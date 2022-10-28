#include <stdio.h>
#include <stdlib.h>
#include "funcoesGerais.h"
#include "funcoesBuscaBin.h"
#include "funcoesImpressaoBin.h"

void funcUm(char *nomeArqEntrada, char *nomeArqSaida) {
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);
    
    FILE* arqSaida;
    arqSaida = fopen(nomeArqSaida, "wb");
    testaErroArquivo(arqSaida);

    regCabecalho aux = inicializaCabecalho();
    atualizaRegCabecalho (arqSaida, aux);
    createTable(arqEntrada, arqSaida, &aux);
    atualizaRegCabecalho (arqSaida, aux); 

    fclose(arqEntrada);
    fclose(arqSaida);

    binarioNaTela(nomeArqSaida);
}

void funcDois(char *nomeArqEntrada) {
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);
    
    regCabecalho aux = recuperaCabecalho(arqEntrada);
    verificaStatusLeitura(aux.status);

    selectFrom(arqEntrada, aux);

    fclose(arqEntrada);
}

void funcTres(char *nomeArqEntrada){
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);

    regCabecalho aux = recuperaCabecalho(arqEntrada);
    verificaStatusLeitura(aux.status);

    selectFromWhere(arqEntrada, aux);

    fclose(arqEntrada);
}

void funcQuatro(char *nomeArqEntrada){
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb+");
    testaErroArquivo(arqEntrada);

    regCabecalho aux = recuperaCabecalho(arqEntrada);
    verificaStatusLeitura(aux.status);
    atualizaStatusEscrita(arqEntrada);

    remocaoLogica(arqEntrada, &aux);
    atualizaRegCabecalho(arqEntrada, aux); 
    
    fclose(arqEntrada);
    binarioNaTela(nomeArqEntrada);
}

void funcCinco(char *nomeArqEntrada){
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb+");
    testaErroArquivo(arqEntrada);

    regCabecalho aux = recuperaCabecalho(arqEntrada);
    verificaStatusLeitura(aux.status);
    atualizaStatusEscrita(arqEntrada);

    insertInto(arqEntrada, &aux);
    atualizaRegCabecalho(arqEntrada, aux);
    fclose(arqEntrada);

    binarioNaTela(nomeArqEntrada);
}

void funcSeis(char *nomeArqEntrada){
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);
    
    FILE* arqSaida;
    arqSaida = fopen("temporario.bin", "wb");
    testaErroArquivo(arqSaida);
    regCabecalho aux = inicializaCabecalho();
    atualizaRegCabecalho(arqSaida, aux);

    aux = recuperaCabecalho(arqEntrada);
    verificaStatusLeitura(aux.status);

    compactacao(arqEntrada, arqSaida, &aux);
    atualizaRegCabecalho(arqSaida, aux); 
    fclose(arqEntrada);
    fclose(arqSaida);

    manipulaArquivoDuplicata(nomeArqEntrada, "temporario.bin");
    
    binarioNaTela(nomeArqEntrada);


    // FILE* arquivo1 = fopen("binario17.bin", "rb+");
    // regCabecalho aux1 = recuperaCabecalho(arquivo1);
    // printf("\n%c %d %d %d %d %d\n", aux1.status, aux1.topo, aux1.proxRRN, aux1.nroRegRem, aux1.nroPagDisco, aux1.qttCompacta);
    // printf("\n\n\n");
    // fclose(arquivo1);
    // FILE *arquivo2 = fopen("correto17.bin", "rb+");
    // regCabecalho aux2 = recuperaCabecalho(arquivo2);
    // printf("\n%c %d %d %d %d %d\n", aux2.status, aux2.topo, aux2.proxRRN, aux2.nroRegRem, aux2.nroPagDisco, aux2.qttCompacta);
    // printf("\n\n\n");
    // fclose(arquivo2);
}

int main(void) {
    int funcionalidade; 
    //char *nomeArqEntrada;
    //char *nomeArqSaida;
    //scanf("%d %ms", &funcionalidade, &nomeArqEntrada);
    char nomeArqEntrada[campoMaximo];
    char nomeArqSaida[campoMaximo];
    scanf("%d %s", &funcionalidade, nomeArqEntrada);

    switch(funcionalidade) {
        case 1:
            //scanf("%ms", &nomeArqSaida);
            scanf("%s", nomeArqSaida);
            funcUm(nomeArqEntrada, nomeArqSaida);
            //free(nomeArqSaida);
            break;
        case 2:
            funcDois(nomeArqEntrada);
            break;
        case 3:
            funcTres(nomeArqEntrada);
            break;
        case 4:
            funcQuatro(nomeArqEntrada);
            break;
        case 5:
            funcCinco(nomeArqEntrada);
            break;
        case 6:
            funcSeis(nomeArqEntrada);
            break; 
        default:
            printf("Comando Não Encontrado \n");
    }

    //free(nomeArqEntrada);
    return 0;

}
