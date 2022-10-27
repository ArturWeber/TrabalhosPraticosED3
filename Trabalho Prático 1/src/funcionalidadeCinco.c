#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerFuncoes.h"

void leString(char *str, int flag){
    getchar();
    char caractere;
    int cont = 0;
    if((caractere = getchar()) == 34){
        while ((caractere = getchar()) != 34){
            str[cont] = caractere;
            cont++;
        }
        str[cont] = '\0';
    }else if((caractere = getchar()) == 'U'){
        scanf("%s", str);

        switch (flag)
        {
        case 0:
            strcpy(str, "");
            break;

        case 1:
            strcpy(str, "$");
            break;
        
        case 2:
            strcpy(str, "$$");
            break;
        
        default:
            break;
        }
        
    }
}

int leInt(){
    getchar();
    char *str;
    int num;
    scanf("%s", str);
    if(strcmp(str, "NULO") == 0){
        return -1;
    }else{
        num = atoi(str);
        return num;
    }
    
}

void insertInto(FILE* arqEntrada, int* flagInseridos, regCabecalho cabecalho) {
    int numInsercao;
    scanf("%d", &numInsercao);

    registro aux[numInsercao];
    char unimed[2];

    for(int i = 0; i < numInsercao; i++){
        scanf("%d", &aux[i].idConecta);
        leString(aux[i].nomePoPs, 0);
        leString(aux[i].nomePais, 0);
        leString(aux[i].siglaPais, 2);
        aux[i].idPoPsConectado = leInt();
        //leString(&aux[i].unidadeMedida, 1);
        //getchar();
        //aux[i].velocidade = leInt();
    }
    printf("%d ", aux[0].idConecta);
    printf("%s ", aux[0].nomePoPs);
    printf("%s ", aux[0].nomePais);
    printf("%s ", aux[0].siglaPais);
    printf("%d ", aux[0].idPoPsConectado);
    //printf("%c\n", aux[0].unidadeMedida);
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