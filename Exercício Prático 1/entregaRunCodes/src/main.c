#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

int main(int argc, char* argv[]) {
    //recebe comando inicial
    //aqui adicionariamos ./file/ no nomeDir para criar uma pasta file para guardar todos os arquivos
    //isso aumentaria a organizacao do codigo mas teriamos que adicionar os arquivos previamente para o runcodes considerar
    //por esse motivo resolvemos nao fazer uma pasta file, arquivos sao lidos e criados no diretorio do makefile
    int comando; 
    char nomeDir[60];
    strcpy(nomeDir, "./");
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