#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerFuncoes.h"


void selectFrom(FILE* arqEntrada){
    registro aux;
    int i, tam, encademento;
    char removido;
    fseek(arqEntrada, 0L, SEEK_END);
    tam = (ftell(arqEntrada)-960)/64;
    i = 0;

    while(i < tam){
        fseek(arqEntrada, 960+(64*i), SEEK_SET);


        fread(&removido, sizeof(char), 1, arqEntrada);
        fread(&encademento, sizeof(int), 1, arqEntrada);
        fread(&aux.idConecta, sizeof(int), 1, arqEntrada);
        fread(aux.siglaPais, sizeof(char), tamSiglaPais, arqEntrada);
        fread(&aux.idPoPsConectado, sizeof(int), 1, arqEntrada);
        fread(&aux.unidadeMedida, sizeof(char), tamUnidadeMedida, arqEntrada);
        fread(&aux.velocidade, sizeof(int), 1, arqEntrada);
        fscanf(arqEntrada, "%[^|]", aux.nomePoPs);
        fseek(arqEntrada, 1, SEEK_CUR);
        fscanf(arqEntrada, "%[^|]", aux.nomePais);



        if(removido == '0'){
            printf("Identificador do ponto: %d\n", aux.idConecta);
            if(strlen(aux.nomePoPs) > 1)
                printf("Nome do ponto: %s\n", aux.nomePoPs);
            if(strlen(aux.nomePais) > 1)
                printf("Pais de localizacao: %s\n", aux.nomePais);
            if(strcmp(aux.siglaPais, "$$"))
                printf("Sigla do pais: %s\n", aux.siglaPais);
            if(aux.idPoPsConectado != -1)
                printf("Identificador do ponto conectado: %d\n", aux.idPoPsConectado);
            if(aux.velocidade != -1)
                printf("Velocidade de transmissao: %d %cbps\n", aux.velocidade, aux.unidadeMedida);
            printf("\n");
        }else{
            printf("registro removido\n");
        }

        i++;
    }

}

void funcDois(char nomeArqEntrada[]){
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);

    selectFrom(arqEntrada);

    fclose(arqEntrada);

}

