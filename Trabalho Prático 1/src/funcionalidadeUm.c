#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerFuncoes.h"

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

void criaInicioRegistro(FILE* arqSaida) {
    fwrite("0", sizeof(char), 1, arqSaida);

    int inicializar = -1;
    fwrite(&inicializar, sizeof(int), 1, arqSaida);
}

void preenchimentoComSifrao(FILE* arqSaida, int tamUsado, int tamMaximo){
    //adiciona lixo em bytes não preenchido no campo
    for (int i = 0; i < tamMaximo - tamUsado; i++){
        fwrite("$", sizeof(char), 1, arqSaida);
    }
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
    int comprimento = strlen(string);
    if(string[0] == ' ') {
        string[0] = '\0';
    } else if (string[comprimento - 1] == ' ') {
        string[comprimento - 1] = '\0';
    }
}

void insereInt(FILE* arqSaida, int insercao, int flagTipagem) {
    int intNulo = -1;

    switch (flagTipagem) {
        case 0:
            if (insercao != 0) {
                fwrite(&insercao, sizeof(int), 1, arqSaida);
            } else {
                fwrite(&intNulo, sizeof(int), 1, arqSaida);
            }
            break;
        case 1:
            if (insercao != '\0') {
                fwrite(&insercao, sizeof(char), 1, arqSaida);
            } else {
                preenchimentoComSifrao(arqSaida, 0, tamUnidadeMedida);
            }
            break;
        default:
            break;
    }
}

void insereString(FILE* arqSaida, char* insercao, int tamanhoCampo, int isFixo) {
    fwrite(insercao, sizeof(char), strlen(insercao), arqSaida);
    if (isFixo) {
        preenchimentoComSifrao(arqSaida, strlen(insercao), tamanhoCampo);
    } else {
        fwrite("|", sizeof(char), 1, arqSaida);
    }
}

void createTable(FILE* arqEntrada, FILE* arqSaida) {

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


        //obs: dar define nos valores de tamanhho de campo

        //Funcoes que criam registro e adicionam campos
        criaInicioRegistro(arqSaida);
        
        insereInt(arqSaida, aux.idConecta, 0);
        insereString(arqSaida, aux.siglaPais, tamSiglaPais, 1);
        insereInt(arqSaida, aux.idPoPsConectado, 0);
        insereInt(arqSaida, aux.unidadeMedida, 1);
        insereInt(arqSaida, aux.velocidade, 0);
        insereString(arqSaida, aux.nomePoPs, 0, 0);
        insereString(arqSaida, aux.nomePais, 0, 0);
        
        int tamOcupadoRegistro = 22 + strlen(aux.nomePoPs) + strlen(aux.nomePais);
        preenchimentoComSifrao(arqSaida, tamOcupadoRegistro, tamRegistro);
    }
}

void funcUm(char *nomeArqEntrada, char *nomeArqSaida) {
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);
    
    FILE* arqSaida;
    arqSaida = fopen(nomeArqSaida, "wb");
    testaErroArquivo(arqSaida);

    criaRegCabecalho(arqSaida);
    createTable(arqEntrada, arqSaida);
    atualizaRegCabecalho(arqSaida);

    // FILE* arqTeste = fopen("teste.bin", "rb");
    // char status;
    // int topo;
    // int proxRRN;
    // int numRegRem;
    // int numPagDisc;
    // int qttCompacta;
    // fread(&status, sizeof(char), 1, arqTeste);
    // fread(&topo, sizeof(int), 1, arqTeste);
    // fread(&proxRRN, sizeof(int), 1, arqTeste);
    // fread(&numRegRem, sizeof(int), 1, arqTeste);
    // fread(&numPagDisc, sizeof(int), 1, arqTeste);
    // fread(&qttCompacta, sizeof(int), 1, arqTeste);
    // printf("\n%c %d %d %d %d %d \n",  status, topo, proxRRN, numRegRem, numPagDisc, qttCompacta);
    // fclose(arqTeste);

    fclose(arqEntrada);
    fclose(arqSaida);

    binarioNaTela(nomeArqSaida);
}
