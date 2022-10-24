#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerFuncoes.h"

void preenchimentoComSifrao(FILE* arqSaida, int tamUsado, int tamMaximo){
    //adiciona lixo em bytes não preenchido no campo
    for (int i = 0; i < tamMaximo - tamUsado; i++){
        fwrite("$", sizeof(char), 1, arqSaida);
    }
}

void criaInicioRegistro(FILE* arqSaida) {
    fwrite("0", sizeof(char), 1, arqSaida);

    int inicializar = -1;
    fwrite(&inicializar, sizeof(int), 1, arqSaida);
}

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
    int aux = strlen(string);
    if(string[0] == ' ') {
        string[0] = '\0';
    }
    if(string[aux] == ' '){
        string[aux] = '\0';
    }
}

void createTable(FILE* arqEntrada, FILE* arqSaida) {

    //cria registro auxiliar e variaveis para armazenar as linhas 
    registro aux;
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

        //ESCREVE VALOR NO ARQUIVO
        //obs: dar define nos valores de tamanhho de campo 
        criaInicioRegistro(arqSaida);

        int intNulo = -1;
        
        fwrite(&aux.idConecta, sizeof(int), 1, arqSaida);

        fwrite(aux.siglaPais, sizeof(char), strlen(aux.siglaPais), arqSaida);
        preenchimentoComSifrao(arqSaida, strlen(aux.siglaPais), tamSiglaPais);

        if (aux.idPoPsConectado != 0) {
            fwrite(&aux.idPoPsConectado, sizeof(int), 1, arqSaida);
            
        } else {
            fwrite(&intNulo, sizeof(int), 1, arqSaida);
        }

        fwrite(&aux.unidadeMedida, sizeof(char), strlen(&aux.unidadeMedida), arqSaida);
        preenchimentoComSifrao(arqSaida, strlen(&aux.unidadeMedida), tamUnidadeMedida);

        if (aux.velocidade != 0) {
            fwrite(&aux.velocidade, sizeof(int), 1, arqSaida);
        } else {
            fwrite(&intNulo, sizeof(int), 1, arqSaida);
        }
        
        fwrite(aux.nomePoPs, sizeof(char), strlen(aux.nomePoPs), arqSaida);
        fwrite("|", sizeof(char), 1, arqSaida);

        fwrite(aux.nomePais, sizeof(char), strlen(aux.nomePais), arqSaida);
        fwrite("|", sizeof(char), 1, arqSaida);
        
        int tamOcupadoRegistro = 22 + strlen(aux.nomePoPs) + strlen(aux.nomePais);
        preenchimentoComSifrao(arqSaida, tamOcupadoRegistro, tamRegistro);
    }
}

void criaRegCabecalho(FILE* arq) {
    fwrite("0", sizeof(char), 1, arq);

    int topo = -1;
    fwrite(&topo, sizeof(int), 1, arq);

    int zero = 0;
    for(int i = 0; i < 4; i++) {
        fwrite(&zero, sizeof(int), 1, arq);
    }

    for(int i = 0; i < 939; i++) {
        fwrite("$", sizeof(char), 1, arq);
    }
}

void funcUm(char nomeArqEntrada[], char nomeArqSaida[]) {
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);
    
    FILE* arqSaida;
    arqSaida = fopen(nomeArqSaida, "wb");
    testaErroArquivo(arqSaida);

    criaRegCabecalho(arqSaida);
    createTable(arqEntrada, arqSaida);
    atualizaRegCabecalho(arqSaida);

    fclose(arqEntrada);
    fclose(arqSaida);

    binarioNaTela(nomeArqSaida);
}