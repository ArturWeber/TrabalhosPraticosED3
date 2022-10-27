#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerFuncoes.h"

void transfString(char linhaInicial[], char linhaFinal[]) {
    int posicao = 0;
    for(unsigned long i = 0; i < (strlen(linhaInicial) - 1); i++) {
        linhaFinal[posicao] = linhaInicial[i];
        if ((linhaInicial[i] == ',') && (linhaInicial[i + 1] == ',' || (i == strlen(linhaInicial) - 2))) {
            linhaFinal[posicao + 1] = ' ';
            posicao++; 
        }
        posicao++;
    }
    linhaFinal[posicao] = '\0';
}

void transfInversaString(char *string) {  
    int comprimento = strlen(string);
    int ultimoDigito = -1 ;
    for (int i = 0; i < comprimento; i++) {
        if (string[i] != ' ') {
            ultimoDigito = i;
        }
    }
    if (ultimoDigito == -1) {
        string[0] = '\0';
    } else {
        string[ultimoDigito + 1] = '\0';
    }
}

void createTable(FILE* arqEntrada, FILE* arqSaida, regCabecalho* cabecalho) {

    //cria registro auxiliar e variaveis para armazenar as linhas 
    registro aux = inicializaRegistro();
    char linhaDestratada[linhaMaxima];
    fgets(linhaDestratada, linhaMaxima, arqEntrada);
    char linhaTratada[linhaMaxima];
    char* token;
    int i = 0;

    //le registro a registro
    while (fgets(linhaDestratada, linhaMaxima, arqEntrada) != NULL) {
        transfString(linhaDestratada, linhaTratada);
        token = strtok(linhaTratada, ",");
        //le campo a campo 
        while(token != NULL) {
            i++;
            switch(i){
                case 1:
                    aux.idConecta = atoi(token);
                    break;
                case 2:
                    strcpy(aux.nomePoPs, token);
                    transfInversaString(aux.nomePoPs);
                    break;
                case 3:
                    strcpy(aux.nomePais, token);
                    transfInversaString(aux.nomePais);
                    break;
                case 4:
                    strcpy(aux.siglaPais, token);
                    transfInversaString(aux.siglaPais);
                    break;
                case 5:
                    aux.idPoPsConectado = atoi(token);
                    break;
                case 6:
                    aux.unidadeMedida = token[0];
                    transfInversaString(&aux.unidadeMedida);
                    break;
                case 7:
                    aux.velocidade = atoi(token);
                    i = 0;
                break;
            }
            token = strtok(NULL, ",");
        }
        cabecalho->proxRRN++;

        //Funcoes que criam registro e adicionam campos
        insereRegistro(arqSaida, aux);
        
    }
    cabecalho->status = '1';
}

void funcUm(char *nomeArqEntrada, char *nomeArqSaida) {
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);
    
    FILE* arqSaida;
    arqSaida = fopen(nomeArqSaida, "wb");
    testaErroArquivo(arqSaida);

    regCabecalho aux = inicializaCabecalho();
    atualizaRegCabecalho (arqSaida, aux);
    createTable(arqEntrada, arqSaida, &aux);
    atualizaRegCabecalho (arqSaida, aux); 

    fclose(arqEntrada);
    fclose(arqSaida);

    binarioNaTela(nomeArqSaida);
}
