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
            if(cabecalho->nroRegRem) {
                fseek(arquivo, (960 + cabecalho->topo * 64) + 1, SEEK_SET);
                fread(&(cabecalho->topo), sizeof(int), 1, arquivo);
                fseek(arquivo, -5, SEEK_CUR);
                criaInicioRegistro(arquivo);
                insereRegistro(arquivo, aux[insercao]);
                cabecalho->nroRegRem--;
            } else {
                fseek(arquivo, (960 + cabecalho->proxRRN * 64), SEEK_SET);
                criaInicioRegistro(arquivo);
                insereRegistro(arquivo, aux[insercao]);
                cabecalho->proxRRN++;
            }
            
        }
    }
    cabecalho->status = '1';
}



void funcCinco(char *nomeArqEntrada){
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb+");
    testaErroArquivo(arqEntrada);
    fclose(arqEntrada);

    regCabecalho aux = recuperaCabecalho(arqEntrada);
    verificaStatusLeitura(aux.status);
    atualizaStatusEscrita(arqEntrada);

    insertInto(arqEntrada, &aux);
    atualizaRegCabecalho(arqEntrada, aux); 

    // FILE* arquivo1 = fopen("correto.bin", "rb+");
    // regCabecalho aux1 = recuperaCabecalho(arquivo1);
    // printf("\n%c %d %d %d %d %d\n", aux1.status, aux1.topo, aux1.proxRRN, aux1.nroRegRem, aux1.nroPagDisco, aux1.qttCompacta);
    // printf("\n\n\n");
    // fclose(arquivo1);
    // FILE *arquivo2 = fopen("errado.bin", "rb+");
    // regCabecalho aux2 = recuperaCabecalho(arquivo2);
    // printf("\n%c %d %d %d %d %d\n", aux2.status, aux2.topo, aux2.proxRRN, aux2.nroRegRem, aux2.nroPagDisco, aux2.qttCompacta);
    // printf("\n\n\n");
    // fclose(arquivo2);

    binarioNaTela(nomeArqEntrada);
}