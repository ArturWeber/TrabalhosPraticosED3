#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerFuncoes.h"

void selectFrom(FILE* arqEntrada){
    registro aux;
    int delim;
    char auxInt[5] = "";
    aux.idPoPsConectado = 0;
    fseek(arqEntrada, 960, SEEK_SET);

    for(int i = 1; i <= 6; i++){
        fread(&aux.idConecta, sizeof(int), 1, arqEntrada);
        fseek(arqEntrada, 1, SEEK_CUR);
        fscanf(arqEntrada, "%[^|]", aux.nomePoPs);
        fseek(arqEntrada, 1, SEEK_CUR);
        fscanf(arqEntrada, "%[^|]", aux.nomePais);
        fseek(arqEntrada, 1, SEEK_CUR);
        fscanf(arqEntrada, "%[^|]", aux.siglaPais);
        fseek(arqEntrada, 1, SEEK_CUR);
        delim = fgetc(arqEntrada);
        if(delim != '|'){
            fseek(arqEntrada, -1, SEEK_CUR);
            fread(&aux.idPoPsConectado, sizeof(int), 1, arqEntrada);
            fseek(arqEntrada, 1, SEEK_CUR);
        }
        delim = fgetc(arqEntrada);
        if(delim != '|'){
            fseek(arqEntrada, -1, SEEK_CUR);
            fscanf(arqEntrada, "%[^|]", aux.unidadeMedida);
            fseek(arqEntrada, 1, SEEK_CUR);
            fread(&aux.velocidade, sizeof(int), 1, arqEntrada);
            fseek(arqEntrada, 1, SEEK_CUR);
        }


        printf("Identificador do ponto: %d\n", aux.idConecta);
        if(strlen(aux.nomePoPs) > 2){
            printf("Nome do ponto: %s\n", aux.nomePoPs);
        }
        if(strlen(aux.nomePais) > 2){
            printf("Pais de localizacao: %s\n", aux.nomePais);
        }
        if(strlen(aux.siglaPais) == 2){
            printf("Sigla do Pais: %s\n", aux.siglaPais);
        }
        if(aux.idPoPsConectado != 0){
            printf("Identificador do ponto conectado: %d\n", aux.idPoPsConectado);
        }
        if(!(strcmp(aux.unidadeMedida, "M")) || !(strcmp(aux.unidadeMedida, "G"))){
            printf("Velocidade de transmissao: %d %sbps\n", aux.velocidade, aux.unidadeMedida);
        }
        printf("\n");
        aux.idPoPsConectado = 0;
        aux.velocidade = 0;
        strcpy(aux.nomePoPs, "");
        strcpy(aux.nomePais, "");
        strcpy(aux.siglaPais, "");
        strcpy(aux.unidadeMedida, "");
        fseek(arqEntrada, 960+(108*(i)), SEEK_SET);
    }


}

void selectFromWhere(FILE* arqEntrada){
    registro aux;

}