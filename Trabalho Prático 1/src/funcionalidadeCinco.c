#include <stdio.h>
#include "headerFuncoes.h"


void insertInto(FILE* arqEntrada, int* flagInseridos, regCabecalho aux) {

}



void funcCinco(char *nomeArqEntrada){
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb+");
    testaErroArquivo(arqEntrada);

    regCabecalho aux = recuperaCabecalho(arqEntrada);
    verificaStatusLeitura(aux.status);
    atualizaStatusEscrita(arqEntrada);

    int flagInseridos[2];
    insertInto(arqEntrada, flagInseridos, aux);
    atualizaRegCabecalho(arqEntrada, 0, 0, 0); 

    fclose(arqEntrada);
    binarioNaTela(nomeArqEntrada);
}