#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

int main(int argc, char* argv[]) {
    //recebe comando inicial
    int comando; 
    char nomeDir[60];
    strcpy(nomeDir, "./file/");
    char nomeArq[30];
    scanf("%d %s", &comando, nomeArq);
    strcat(nomeDir, nomeArq);

    //chama comandos
    if(comando == 1) {
        FILE *arqArmaz = fopen(nomeDir, "wb");

        funcionalidade1(arqArmaz);

        fclose(arqArmaz);

        //saida da funcao 1 especificada na documentacao 
        binarioNaTela(nomeDir);
    }else if(comando == 2) {
        FILE *arqArmaz = fopen(nomeDir, "rb");
        if(arqArmaz == NULL) {
            printf("Falha no processamento do arquivo");
            exit(0);
        }

        funcionalidade2(arqArmaz);
        
        fclose(arqArmaz);
    }else if (comando == 3) {
        FILE *arqArmaz = fopen(nomeDir, "rb");
        if(arqArmaz == NULL) {
            printf("Falha no processamento do arquivo");
            exit(0);
        }

        funcionalidade3(arqArmaz);

        fclose(arqArmaz);
    } else {
        printf("Erro: Comando não encontrado");
        exit(0);
    }
}