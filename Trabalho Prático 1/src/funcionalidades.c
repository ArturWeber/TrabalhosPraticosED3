#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerFuncoes.h"

void funcUm(char nomeArqEntrada[], char nomeArqSaida[]) {
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "r");
    
    FILE* arqSaida;
    arqSaida = fopen(nomeArqSaida, "wb");

    if(arqEntrada == NULL || arqSaida == NULL) {
        imprimeErroArquivo();
        exit(-1);
    }

    criaRegCabecalho(arqSaida);
    createTable(arqEntrada, arqSaida);
    fclose(arqEntrada);
    fclose(arqSaida);
}

void funcDois(char nomeArqEntrada[]){
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");

    if(arqEntrada == NULL){
        imprimeErroArquivo();
        exit(-1);
    }
    selectFrom(arqEntrada);
    fclose(arqEntrada);
}

void funcTres(char nomeArqEntrada[]){
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");

    if(arqEntrada == NULL){
        imprimeErroArquivo();
        exit(-1);
    }

    selectFromWhere(arqEntrada);
}

