#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

int main(int argc, char* argv[]) {
    //recebe comando inicial
    int comando; 
    char nomeArq[30];
    scanf("%d %s", &comando, nomeArq);

    //recebe parâmetros iniciais
    if(comando == 1) {
        FILE *arqArmaz = fopen(nomeArq, "w");
        funcionalidade1(arqArmaz);
        fclose(arqArmaz);
    }else if(comando == 2) {
        FILE *arqArmaz = fopen(nomeArq, "r");
        funcionalidade2();
        fclose(arqArmaz);
    }else if (comando == 3) {
        FILE *arqArmaz = fopen(nomeArq, "r");
        funcionalidade3();
        fclose(arqArmaz);
    } else {
        printf("Erro: Comando não encontrado");
        exit(0);
    }
}