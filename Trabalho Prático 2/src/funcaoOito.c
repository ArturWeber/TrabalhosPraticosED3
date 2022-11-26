/************************************************************
 *            Trabalho Prático 2 - SCC0607                   *
 *                                                           *
 *      Nome: Artur Brenner Weber                            *
 *      nUSP: 12675451    Participacao: 100%                 *
 *      Nome: Aruan  Bretas de Oliveira Filho                *
 *      nUSP: 12609731    Participacao: 65%                  *
 *      Data de última atualizacao: 25/11/2022               *
 *      Ambiente de Desenvolv: VSCode 1.72.2                 *
 *                                                           *
 *             Conteudo arquivo funcoesBuscaBin:             *
 *   Funcoes secundarias das funcionalidades                 *
 *                  8 (createIndex)                          *
 * Organizadas juntas pois envolvem funcoes em comum.        *
*************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "funcoesGeraisT1.h"
#include "funcoesGeraisT2.h"
#include "funcoesImpressaoBin.h"
#include "funcoesBuscaBin.h"
#include "funcaoOito.h"

//Funcionalidade responsavel pela busca do indice na arvore
int buscaRegistroIndice(FILE* arqSaida, int chaveBuscada, int RRNnoAtual, int* numPagDisco) {
    (*numPagDisco)++;
    int RRNencontrado;
    //le o no atual
    registroIndice noAtual = leRegistroIndice(arqSaida, RRNnoAtual);

    //procura ou o valor ou onde inserir
    int posPonteiro = posicaoInserir(noAtual, chaveBuscada);

    //se encontrou o valor, o retorna
    if ((posPonteiro < ordemArvore - 1) && (noAtual.dados[posPonteiro].chave == chaveBuscada)) { 
        RRNencontrado = noAtual.dados[posPonteiro].referencia;
        return RRNencontrado;
    } 
    if (noAtual.folha == '1') {
        //Se for folha e ele nao encontrou é porque nao ha o valor em armazenamento
        RRNencontrado = -1;
        return RRNencontrado;
    }
    //Se nao for folha e nao encontrou, desce para buscar mais 
    int RRNfilho = noAtual.ponteiros[posPonteiro];
    RRNencontrado = buscaRegistroIndice(arqSaida, chaveBuscada, RRNfilho, numPagDisco);
    return RRNencontrado;

}

//Funcao secundaria da funcionalidade 8, muito semelhante a funcionalidade 3
//tendo como diferenca ter que diferenciar quando a busca eh pelo
//idConecta, a qual deve ser realizada na arvore-b(arquivo de indice)
//sendo mais eficiente do que a busca sequecial
void selectFromWhereIndice(FILE* arqEntrada, FILE* arqIndice, regCabecalho aux, regCabecalhoIndice auxIndice) {
    //Coleta o numero de buscas 
    int numBuscas;
    scanf("%d", &numBuscas);

    //Armazena as especificacoes de cada busca, isto e, o campo, seu valor e o indice do campo
    char descricaoCampo[numBuscas][campoMaximo];
    char valorCampoBuscado[numBuscas][campoMaximo];
    int indiceCampoBuscado[numBuscas];
    leCamposDeBusca(descricaoCampo, valorCampoBuscado, indiceCampoBuscado, numBuscas);
   
    //Efetua cada busca
    for(int i = 0; i < numBuscas; i++){
        fseek(arqEntrada, 960, SEEK_SET);
        printf("Busca %d\n", i + 1);
        int encadeamento;
        char removido;
        int numEncontrados = 0;
        int numPagDisco = 0;
        registro lido = inicializaRegistro();

        //se for busca por idconecta usa arvore B
        if (indiceCampoBuscado[i] == 0) {
            //comeca buscando pela raiz, e retorna o valor do rrn encontrado ou -1 se nao encontrar
            int chaveBuscada = atoi(valorCampoBuscado[i]);
            int RRNencontrado = buscaRegistroIndice(arqIndice, chaveBuscada, auxIndice.noRaiz, &numPagDisco);

            if (RRNencontrado != -1) {
                fseek(arqEntrada, (RRNencontrado * 64) + 5, SEEK_CUR);

                //le todos os campos de um registro
                leRegistro(arqEntrada, &lido);
                imprimeRegistro(lido);
                numEncontrados++;
                printf("\n");
            }

            numPagDisco += 3;
        } else {
            //Le registro a registro procurando o que busca
            for(int rrn = 0; rrn < aux.proxRRN; rrn++){
            
                fread(&removido, sizeof(char), 1, arqEntrada);
                //Se for removido para de ler 
                if(removido == '1'){
                    leLixo(arqEntrada, 63);
                    continue;
                }

                //Armazena registro na variavel auxiliar
                lido = inicializaRegistro();
                fread(&encadeamento, sizeof(int), 1, arqEntrada);
                //le todos os campos de um registro
                leRegistro(arqEntrada, &lido);

                //Se encontrou o campo, imprime-o
                if (campoEncontrado(indiceCampoBuscado[i], valorCampoBuscado[i], lido)) {
                    numEncontrados++;
                    imprimeRegistro(lido);
                    printf("\n");
                }

                int comprimentoLixo = 42 - strlen(lido.nomePoPs) - strlen(lido.nomePais);
                leLixo(arqEntrada, comprimentoLixo);

            }
            numPagDisco = aux.nroPagDisco;
        }
        
        //Caso nao encontrou nenhum campo, imprime mensagem
        if (!numEncontrados){
            printf("Registro inexistente.\n");    
            printf("\n");
        }

        printf("Numero de paginas de disco: %d\n", numPagDisco);        
        printf("\n");
    }
}