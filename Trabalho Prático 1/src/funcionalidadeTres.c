#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerFuncoes.h"

void funcTres(char nomeArqEntrada[]){
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");

    if(arqEntrada == NULL){
        imprimeErroArquivo();
        exit(-1);
    }

    selectFromWhere(arqEntrada);
}
