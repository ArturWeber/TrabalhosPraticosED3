#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "headerFuncoes.h"

void imprimeInt(int impressao, char *apresentacao, int flagTipagem) {
    switch (flagTipagem) {
    case 0:
        if (impressao != -1) {
            printf(apresentacao, impressao);
        }
        break;
    case 1:
        if (impressao != '$') {
            printf(apresentacao, impressao);
        }
        break;
    default:
        break;
    }
    
}

void imprimeString(char *impressao, char *apresentacao) {
    if (impressao[0] != '$' && impressao[0] != '\0' && strlen(impressao) > 1) {
        printf(apresentacao, impressao);
    }
    impressao[0] = '\0';
}


void selectFrom(FILE* arqEntrada){
    registro aux;
    int encadeamento;
    char removido;
    fseek(arqEntrada, 0L, SEEK_END);
    int tamanhoArq = ftell(arqEntrada);
    int numRegistros = (tamanhoArq - 960) / 64;
    int pagDisco = (int) ceil((tamanhoArq) / (64.0 * 15.0));

    if (pagDisco == 1) {
        printf("Registro inexistente.\n");
        printf("\n");
    }
    
    //zerando campos variados que estavam dando problema no primeiro caso
    strcpy(aux.nomePais, "");
    strcpy(aux.nomePoPs, "");

    int i = 0;
    while(i < numRegistros){
        fseek(arqEntrada, 960 + (64 * i), SEEK_SET);
        i++;


        fread(&removido, sizeof(char), 1, arqEntrada);
        if(removido == '1'){
            continue;
        }

        fread(&encadeamento, sizeof(int), 1, arqEntrada);
        fread(&aux.idConecta, sizeof(int), 1, arqEntrada);
        fread(aux.siglaPais, sizeof(char), tamSiglaPais, arqEntrada);
        fread(&aux.idPoPsConectado, sizeof(int), 1, arqEntrada);
        fread(&aux.unidadeMedida, sizeof(char), tamUnidadeMedida, arqEntrada);
        fread(&aux.velocidade, sizeof(int), 1, arqEntrada);
        fscanf(arqEntrada, "%[^|]", aux.nomePoPs);
        fseek(arqEntrada, 1, SEEK_CUR);
        fscanf(arqEntrada, "%[^|]", aux.nomePais);

        imprimeInt(aux.idConecta, "Identificador do ponto: %d\n", 0);
        imprimeString(aux.nomePoPs, "Nome do ponto: %s\n");
        imprimeString(aux.nomePais, "Pais de localizacao: %s\n");
        imprimeString(aux.siglaPais, "Sigla do pais: %s\n");
        imprimeInt(aux.idPoPsConectado, "Identificador do ponto conectado: %d\n", 0);
        imprimeInt(aux.velocidade, "Velocidade de transmissao: %d", 0);
        imprimeInt(aux.unidadeMedida, " %cbps\n", 1);

        printf("\n");
    }

    printf("Numero de paginas de disco: %d\n", pagDisco);
    printf("\n");

}

void funcDois(char nomeArqEntrada[]){
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);
    verificaStatus(arqEntrada);

    selectFrom(arqEntrada);

    fclose(arqEntrada);

}
