#include <stdio.h>
#include <string.h>

#include "funcoesGeraisT1.h"
#include "funcoesGeraisT2.h"
#include "funcoesBuscaBin.h"
#include "funcoesImpressaoBin.h"
#include "funcaoOito.h"
#include "funcaoDez.h"

//Imprime registro parcialmente
void imprimeRegistroMultiplo(registro auxPrimeiro, registro auxSegundo) {
    imprimeInt(auxPrimeiro.idConecta, "Identificador do ponto: %d\n", 0);
    imprimeString(auxPrimeiro.nomePoPs, "Nome do ponto: %s\n");
    imprimeString(auxPrimeiro.nomePais, "Pais de localizacao: %s\n");
    imprimeString(auxPrimeiro.siglaPais, "Sigla do pais: %s\n");
    imprimeInt(auxPrimeiro.idPoPsConectado, "Identificador do ponto conectado: %d\n", 0);
    imprimeString(auxSegundo.nomePoPs, "Nome do ponto conectado: %s\n");
    imprimeString(auxSegundo.nomePais, "Nome do pais conectado: %s\n");
    imprimeString(auxSegundo.siglaPais, "Sigla do pais: %s\n");
    imprimeInt(auxPrimeiro.velocidade, "Velocidade de transmissao: %d", 0);
    imprimeInt(auxPrimeiro.unidadeMedida, " %cbps\n", 1);
}

void selectFromWhereMultiplasTabelas(FILE* arqEntrada, FILE* arqSaida, FILE* arqIndice, regCabecalho auxEntrada, regCabecalhoIndice auxIndice) {
   
    //lida com os campos buscados caso a funcao precise ser expandida para outros campos fora idConecta e idPoPsConectado
    //int tipoCampo1 = descobreCampoBuscado(nomeCampoPrim);
    //int tipoCampo2 = descobreCampoBuscado(nomeCampoSeg); 

    //Efetua a busca 
    fseek(arqEntrada, 960, SEEK_SET);
    int encadeamento;
    char removido;
    int numEncontrados = 0;
    //Le registro a registro procurando o que busca
    for(int rrn = 0; rrn < auxEntrada.proxRRN; rrn++){
        
        fread(&removido, sizeof(char), 1, arqEntrada);
        //Se for removido para de ler
        if(removido == '1'){
            leLixo(arqEntrada, 63);
            continue;
        }

        //Armazena registro arquivo um na variavel auxiliar
        registro regEntrada = inicializaRegistro();
        fread(&encadeamento, sizeof(int), 1, arqEntrada);
        //le todos os campos de um registro
        leRegistro(arqEntrada, &regEntrada);

        //busca o idPoPsConectado do arquivo um no indice do arquivo dois
        int numPagDisco = 0;
        int chaveBuscada = regEntrada.idPoPsConectado;
        int rrnEncontrado = buscaRegistroIndice(arqIndice, chaveBuscada, auxIndice.noRaiz, &numPagDisco);
        
        //le final do arquivo um
        int comprimentoLixo = 42 - strlen(regEntrada.nomePoPs) - strlen(regEntrada.nomePais);
        leLixo(arqEntrada, comprimentoLixo);

        //Se encontrou o campo, coleta e imprime-o
        if (rrnEncontrado == -1) {
            continue;
        }
        
        //le registro no arquivo dois 
        fseek(arqSaida, 960 + (64 * rrnEncontrado), SEEK_SET);
        fread(&removido, sizeof(char), 1, arqSaida);
        //Se for removido para de ler
        if(removido == '1'){
            continue;
        }

        //Armazena registro arquivo um na variavel auxiliar
        registro regSaida = inicializaRegistro();
        fread(&encadeamento, sizeof(int), 1, arqSaida);
        //le todos os campos de um registro
        leRegistro(arqSaida, &regSaida);

        //imprime o registro caso achou
        numEncontrados++;
        imprimeRegistroMultiplo(regEntrada, regSaida);
        printf("\n");

    }
    
    //Caso nao encontrou nenhum campo, imprime mensagem
    if (!numEncontrados){
        printf("Registro inexistente.\n");    
        printf("\n");
    }
}