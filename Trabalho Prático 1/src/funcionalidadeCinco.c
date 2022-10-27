#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerFuncoes.h"

int gravaInt(char* entrada) {
    if (!strcmp(entrada, "NULO")) {
        return 0;
    } else {
        return atoi(entrada);
    }
}

void insertInto(FILE* arquivo, regCabecalho* cabecalho) {
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
            switch(indice){
                case 0:
                    aux[insercao].idConecta = gravaInt(entrada[indice]);
                    break;
                case 1:
                    strcpy(aux[insercao].nomePoPs, entrada[indice]);
                    break;
                case 2:
                    strcpy(aux[insercao].nomePais, entrada[indice]);
                    break;
                case 3:
                    strcpy(aux[insercao].siglaPais, entrada[indice]);
                    break;
                case 4:
                    aux[insercao].idPoPsConectado = gravaInt(entrada[indice]);
                    break;
                case 5:
                    aux[insercao].unidadeMedida = entrada[indice][0];
                    break;
                case 6:
                    aux[insercao].velocidade = gravaInt(entrada[indice]);
                break;
            }
        }

        for(int insercao = 0; insercao < numInsercoes; insercao++) {
            insereInt(arquivo, aux[insercao].idConecta, 0);
            insereString(arquivo, aux[insercao].siglaPais, tamSiglaPais, 1);
            insereInt(arquivo, aux[insercao].idPoPsConectado, 0);
            insereInt(arquivo, aux[insercao].unidadeMedida, 1);
            insereInt(arquivo, aux[insercao].velocidade, 0);
            insereString(arquivo, aux[insercao].nomePoPs, 0, 0);
            insereString(arquivo, aux[insercao].nomePais, 0, 0);
            cabecalho->nroRegRem--;
        }

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

    insertInto(arqEntrada, &aux);
    atualizaRegCabecalho(arqEntrada, aux); 

    fclose(arqEntrada);
    binarioNaTela(nomeArqEntrada);
}