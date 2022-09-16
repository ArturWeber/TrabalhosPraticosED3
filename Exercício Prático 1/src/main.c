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
        FILE *arqArmaz = fopen(nomeArq, "wb");

        funcionalidade1(arqArmaz);


        fclose(arqArmaz);

        //saida da funcao 1 especificada na documentacao 
        binarioNaTela(nomeArq);
    }else if(comando == 2) {
        FILE *arqArmaz = fopen(nomeArq, "rb");
        if(arqArmaz == NULL) {
            printf("Falha no processamento do arquivo");
            exit(0);
        }

        funcionalidade2(arqArmaz);
        
        fclose(arqArmaz);
    }else if (comando == 3) {
        FILE *arqArmaz = fopen(nomeArq, "rb");
        if(arqArmaz == NULL) {
            printf("Falha no processamento do arquivo");
            exit(0);
        }

        funcionalidade3();

        fclose(arqArmaz);
    } else {
        printf("Erro: Comando não encontrado");
        exit(0);
    }
}


//FAZER MANEIRA DE ALTERAR RAPIDAMENTE OS VALORES DE COMPRIMENTO DOS PARAMETROS!! 
//OU REDUZIR UTILIZACAO DO TAMANHO NAS FUNCOES
//OU USAR VARIAVEL GLOBAL ---------------------------------> ESCOLHI ESSE!
//OU USAR FUNCOES QUE RETORNEM O TAMANHO TIPO STRLEN

//FAZER FUNCAO COM OS PRINTS DE ERROS 

//VER SE CRASHA SE O INPUT FOR MTO GRANDE!!