#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerFuncoes.h"

void gravaInt(int* destino, char* entrada, int flagTipagem) {
    switch (flagTipagem) {
        case 0:
            if (strcmp(entrada, "NULO")) {
                (*destino) = -1;
            } else {
                (*destino) = atoi(entrada);
            }
            break;
        case 1:
            if (strcmp(entrada, "NULO")) {
                (*destino) = '$';
            } else {
                (*destino) = (*entrada);
            }
            break;
        default:
            break;
    }
}

void gravaString (char* destino, char* entrada) {
    if (strcmp(entrada, "NULO")) {
        strcpy(entrada, "");
    } else {
        strcpy(destino, entrada);
    }
} 

void gravaRegistroMemoria(registro aux, char entrada[7][campoMaximo]) {
    gravaInt(&aux.idConecta, entrada[0], 0);
    gravaString(aux.nomePoPs, entrada[1]);
    gravaString(aux.nomePais, entrada[2]);
    gravaString(aux.siglaPais, entrada[3]);
    gravaInt(&aux.idPoPsConectado, entrada[4], 0);
    gravaInt(&aux.unidadeMedida, entrada[5], 1);
    gravaInt(&aux.velocidade, entrada[6], 0);
}

void insertInto(FILE* arqEntrada, int* flagInseridos, regCabecalho cabecalho) {
    int numInsercoes;
    scanf("%d", &numInsercoes);

    registro aux[numInsercoes];
    char entrada[7][campoMaximo];
    for (int insercao = 0; insercao < numInsercoes; insercao++) {
        for (int indice = 0; indice < 7; indice++) {
            if(temAspas(indice, 1)) {
                scan_quote_string(entrada[indice]);
            } else {
                scanf(" %s", entrada[indice]);
            }   
        }
        gravaRegistroMemoria(aux[insercao], entrada);
        
        imprimeInt(aux[insercao].idConecta, "Identificador do ponto: %d\n", 0);
        imprimeString(aux[insercao].nomePoPs, "Nome do ponto: %s\n");
        imprimeString(aux[insercao].nomePais, "Pais de localizacao: %s\n");
        imprimeString(aux[insercao].siglaPais, "Sigla do pais: %s\n");
        imprimeInt(aux[insercao].idPoPsConectado, "Identificador do ponto conectado: %d\n", 0);
        imprimeInt(aux[insercao].velocidade, "Velocidade de transmissao: %d", 0);
        imprimeInt(aux[insercao].unidadeMedida, " %cbps\n", 1);

        printf("\n");
    }

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