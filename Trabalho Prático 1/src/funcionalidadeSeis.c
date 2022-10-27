#include <stdio.h>
#include "headerFuncoes.h"


void Compactacao(FILE* arquivo, regCabecalho* cabecalho){
    int encadeamento = -1;
    while(cabecalho->topo != -1){
        fseek(arquivo, 961+(cabecalho->topo * 64), SEEK_SET);
        fread(cabecalho->topo, sizeof(int), 1, arquivo);
        fseek(arquivo, -5, SEEK_CUR);
        fwrite("0", sizeof(char), 1, arquivo);
        fwrite(&encadeamento, sizeof(int), 1, arquivo);
        cabecalho->nroRegRem--;
    }
    cabecalho->qttCompacta++;
}

void funcSeis(char *nomeArqEntrada){
    FILE* arqEntrada;
    FILE* arqSaida;
    arqEntrada = fopen(nomeArqEntrada, "rb+");
    arqSaida = fopen("SUB.bin", "wb+");
    testaErroArquivo(arqEntrada);

    regCabecalho aux = recuperaCabecalho(arqEntrada);
    verificaStatusLeitura(aux.status);
    atualizaStatusEscrita(arqEntrada);

    Compactacao(arqEntrada, &aux);
    atualizaRegCabecalho(arqEntrada, aux); 
    
    fclose(arqEntrada);
    binarioNaTela(nomeArqEntrada);
}