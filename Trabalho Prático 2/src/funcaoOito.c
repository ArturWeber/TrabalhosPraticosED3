#include <stdio.h>
#include <string.h>
#include "funcoesGeraisT1.h"
#include "funcoesGeraisT2.h"
#include "funcaoOito.h"

void selectFromWhereIndice(FILE* arqEntrada, FILE* arqIndice, regCabecalho aux) {
    //Coleta o numero de buscas 
    int numBuscas;
    scanf("%d", &numBuscas);

    //Armazena as especificacoes de cada busca, isto e, o campo, seu valor e o indice do campo
    char descricaoCampo[numBuscas][campoMaximo];
    char valorCampoBuscado[numBuscas][campoMaximo];
    int indiceCampoBuscado[numBuscas];
    for (int i = 0; i < numBuscas; i++){
        scanf("%s", descricaoCampo[i]);
        indiceCampoBuscado[i] = descobreCampoBuscado(descricaoCampo[i]);
        //Se tiver aspas, usa a funcao de ler aspas, senao, usa scanf
        if (temAspas(indiceCampoBuscado[i], 0)) {
            scan_quote_string(valorCampoBuscado[i]);
        }else {
            scanf("%s", valorCampoBuscado[i]);
        }
        
    }
   
    //Efetua cada busca
    for(int i = 0; i < numBuscas; i++){
        fseek(arqEntrada, 960, SEEK_SET);
        printf("Busca %d\n", i + 1);
        int encadeamento;
        char removido;
        int numEncontrados = 0;
        //Le registro a registro procurando o que busca
        for(int rrn = 0; rrn < aux.proxRRN; rrn++){
            
            fread(&removido, sizeof(char), 1, arqEntrada);
            //Se for removido para de ler 
            if(removido == '1'){
                leLixo(arqEntrada, 63);
                continue;
            }

            //Armazena registro na variavel auxiliar
            registro aux = inicializaRegistro();
            fread(&encadeamento, sizeof(int), 1, arqEntrada);
            //le todos os campos de um registro
            leRegistro(arqEntrada, &aux);

            
            //Se encontrou o campo, imprime-o
            if (campoEncontrado(indiceCampoBuscado[i], valorCampoBuscado[i], aux)) {
                numEncontrados++;
                imprimeRegistro(aux);
                printf("\n");
            }

            int comprimentoLixo = 42 - strlen(aux.nomePoPs) - strlen(aux.nomePais);
            leLixo(arqEntrada, comprimentoLixo);

        }
        
        //Caso nao encontrou nenhum campo, imprime mensagem
        if (!numEncontrados){
            printf("Registro inexistente.\n");    
            printf("\n");
        }

        printf("Numero de paginas de disco: %d\n", aux.nroPagDisco);        
        printf("\n");

        //free(descricaoCampo);
    }
}