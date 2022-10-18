#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerFuncoes.h"

void criaRegCabecalho(FILE* arq) {
    fwrite("1", sizeof(char), 1, arq);
    int topo = -1;
    fwrite(&topo, sizeof(int), 1, arq);
    int zero = 0;
    for(int i = 0; i < 4; i++) {
        fwrite(&zero, sizeof(int), 1, arq);
    }
    for(int i = 0; i < 939; i++) {
        fwrite("$", sizeof(char), 1, arq);
    }
}

void createTable(FILE* arqEntrada, FILE* arqSaida) {
    registro aux;
    char linha[linhaMaxima];
    int i = 0;
    char* token;


    //PROBLEMA ESTA AQUI ARUAN!! esse while so consegue ler registros com todos os campos 
    while (fgets(linha, linhaMaxima, arqEntrada) != NULL) {
        token = strtok(linha, ",");
        while(token != NULL) {
            i++;
            switch(i){
                case 1:
                    aux.idConecta = atoi(token);
                    break;
                case 2:
                    strcpy(aux.nomePoPs, token);
                    break;
                case 3:
                    strcpy(aux.nomePais, token);
                    break;
                case 4:
                    strcpy(aux.siglaPais, token);
                    break;
                case 5:
                    aux.idPoPsConectado = atoi(token);
                    break;
                case 6:
                    aux.unidadeMedida = token[0];
                    break;
                case 7:
                    aux.velocidade = atoi(token);
                    i = 0;
                break;
            }
            token = strtok(NULL, ",");
        }
        printf("%s\n", aux.nomePais);
    }
}

void funcUm(char nomeArqEntrada[], char nomeArqSaida[]) {
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "r");
    
    FILE* arqSaida;
    arqSaida = fopen(nomeArqSaida, "w");

    if(arqEntrada == NULL || arqSaida == NULL) {
        imprimeErroArquivo();
        exit(-1);
    }

    criaRegCabecalho(arqSaida);
    createTable(arqEntrada, arqSaida);
}
