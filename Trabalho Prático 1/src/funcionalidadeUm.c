#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerFuncoes.h"

/*
void createTable(FILE* arqEntrada, FILE* arqSaida) {
    registro aux;
    int tamUsado;

    //strings auxiliares
    char idCon[10] = "";
    char idPoPs[10] = "";
    char vel[10] = "";
    char caractere[2] = "";

    //inteiros auxiliares
    int tamNomePoPs = 0;
    int tamNomePais = 0;
    int tamSiglaPais = 0;
    int tamUniMed = 0;
    int tamidPoPs = 0;
    int tamVel = 0;

    int contvir;//contador de virgulas

    fseek(arqEntrada, 79, SEEK_SET);
    
    while((caractere[0] = (char) fgetc(arqEntrada)) != '\0' && !(feof(arqEntrada))){
        contvir = 0;
        tamUsado = 0;
        tamNomePoPs = 0;
        tamNomePais = 0;
        tamSiglaPais = 0;
        tamUniMed = 0;
        tamidPoPs = 0;
        tamVel = 0;
        //esse laço é responsavel por pegar caractere por caractere até acabar a linha
        do{
            if(caractere[0] == ','){//verifica se o caractere pego é uma virgula pra add as info em outro campo
                contvir++;
                continue;
            }
            switch (contvir) {
                case 0:
                    strcat(idCon, caractere);
                    break;
                
                case 1:
                    strcat(aux.nomePoPs, caractere);
                    tamNomePoPs++;
                    break;

                case 2:
                    strcat(aux.nomePais, caractere);
                    tamNomePais++;
                    break;
                
                case 3:
                    strcat(aux.siglaPais, caractere);
                    tamSiglaPais++;
                    break;

                case 4:
                    strcat(idPoPs, caractere);
                    tamidPoPs = 1;
                    break;

                case 5:
                    strcpy(aux.unidadeMedida, caractere);
                    tamUniMed++;
                    break;
                
                case 6:
                    strcat(vel, caractere);
                    tamVel = 1;
                    break;

                default:
                    break;
            }
            
            
        }while ((caractere[0] = (char) fgetc(arqEntrada)) != '\n' && !(feof(arqEntrada)));

        //caractere[0] = '\0';

        //transforma em inteiro o conteudo dessas strings auxiliares
        aux.idConecta = atoi(idCon);
        aux.idPoPsConectado = atoi(idPoPs);
        aux.velocidade = atoi(vel);

        criaInicioRegistro(arqSaida);

        //adiciona no arquivo de saida cada campo
        fwrite(&aux.idConecta, sizeof(int), 1, arqSaida);

        if(tamSiglaPais != 0) {
            fwrite(aux.siglaPais, sizeof(char), tamSiglaPais, arqSaida);
        }
        if(tamidPoPs == 1 && aux.idPoPsConectado != 0) {
            fwrite(&aux.idPoPsConectado, sizeof(int), tamidPoPs, arqSaida);
        }
        if(tamUniMed != 0) {
            fwrite(aux.unidadeMedida, sizeof(char), tamUniMed, arqSaida);
        } else {
            tamidPoPs = 0;
        }
        if(tamVel == 1 && aux.velocidade != 0) {
            fwrite(&aux.velocidade, sizeof(int), tamVel, arqSaida);
        } else{
            tamVel = 0;
        }
        if(tamNomePoPs != 0) {
            fwrite(aux.nomePoPs, sizeof(char), tamNomePoPs, arqSaida);
        }
        fwrite("|", sizeof(char), 1, arqSaida);
        if(tamNomePais != 0) { 
            fwrite(aux.nomePais, sizeof(char), tamNomePais, arqSaida);
        }
        fwrite("|", sizeof(char), 1, arqSaida);
           
        tamUsado = 4 + tamNomePais + tamNomePoPs + tamSiglaPais + (tamidPoPs * 4) + (tamVel * 4) + 7;

        TratamentoDeRegistro(arqSaida, tamUsado);
        
        //reinicializa strings para uso de concatenação
        strcpy(idCon, "");
        strcpy(idPoPs, "");
        strcpy(vel, "");
        strcpy(aux.nomePais, "");
        strcpy(aux.nomePoPs, "");
        strcpy(aux.siglaPais, "");
        aux.velocidade = 0;
        aux.idPoPsConectado = 0;

    }
}
*/



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

void transformadaString(char linhaInicial[], char linhaFinal[]) {
    int posicao = 0;
    for(unsigned long i = 0; i < (strlen(linhaInicial) - 2); i++) {
        linhaFinal[posicao] = linhaInicial[i];
        if ((linhaInicial[i] == ',') && (linhaInicial[i + 1] == ',' || (i == strlen(linhaInicial) - 3))) {
            linhaFinal[posicao + 1] = ' ';
            posicao++; 
        }
        posicao++;
    }
    linhaFinal[posicao] = '\0';
}

void removeEspacos(char *string) {
    if(string[0] == ' ') {
        string[0] = '\0';
    }
}

void createTable(FILE* arqEntrada, FILE* arqSaida) {
    criaInicioRegistro(arqSaida);

    //cria registro auxiliar e variaveis para armazenar as linhas 
    registro aux;
    char linhaDestratada[linhaMaxima];
    fgets(linhaDestratada, linhaMaxima, arqEntrada);
    char linhaTratada[linhaMaxima];
    char* token;
    int i = 0;

    while (fgets(linhaDestratada, linhaMaxima, arqEntrada) != NULL) {
        transformadaString(linhaDestratada, linhaTratada);
        token = strtok(linhaTratada, ",");
        while(token != NULL) {
            i++;
            switch(i){
                case 1:
                    aux.idConecta = atoi(token);
                    break;
                case 2:
                    strcpy(aux.nomePoPs, token);
                    removeEspacos(aux.nomePoPs);
                    break;
                case 3:
                    strcpy(aux.nomePais, token);
                    removeEspacos(aux.nomePais);
                    break;
                case 4:
                    strcpy(aux.siglaPais, token);
                    removeEspacos(aux.siglaPais);
                    break;
                case 5:
                    aux.idPoPsConectado = atoi(token);
                    break;
                case 6:
                    aux.unidadeMedida = token[0];
                    removeEspacos(&aux.unidadeMedida);
                    break;
                case 7:
                    aux.velocidade = atoi(token);
                    i = 0;
                break;
            }
            token = strtok(NULL, ",");
        }

        int intNulo = -1;

        if (aux.idConecta != 0) {
            fwrite(&aux.idConecta, sizeof(int), 1, arqSaida);
        }

        fwrite(aux.siglaPais, sizeof(char), strlen(aux.siglaPais), arqSaida);
        preenchimentoComSifrao(arqSaida, strlen(aux.siglaPais), 2);

        if (aux.idPoPsConectado != 0) {
            fwrite(&aux.idPoPsConectado, sizeof(int), 1, arqSaida);
        } else {
            fwrite(&intNulo, sizeof(int), 1, arqSaida);
        }

        if (aux.unidadeMedida != ' ') {
            fwrite(&aux.unidadeMedida, sizeof(char), 1, arqSaida);
        } else {
            preenchimentoComSifrao(arqSaida, 0, 1);
        }

        if (aux.velocidade != 0) {
            fwrite(&aux.velocidade, sizeof(int), 1, arqSaida);
        } else {
            fwrite("$", sizeof(char), 1, arqSaida);
        }
        
        fwrite(aux.nomePoPs, sizeof(char), strlen(aux.nomePoPs), arqSaida);
        fwrite("|", sizeof(char), 1, arqSaida);

        fwrite(aux.nomePais, sizeof(char), strlen(aux.nomePais), arqSaida);
        fwrite("|", sizeof(char), 1, arqSaida);
        
        int tamOcupadoRegistro = 22 + strlen(aux.nomePoPs) + strlen(aux.nomePais);
        preenchimentoComSifrao(arqSaida, tamOcupadoRegistro, 64);

    }
}

void criaRegCabecalho(FILE* arq) {
    fwrite("1", sizeof(char), 1, arq);

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
    arqEntrada = fopen(nomeArqEntrada, "r");
    
    FILE* arqSaida;
    arqSaida = fopen(nomeArqSaida, "wb");

    if(arqEntrada == NULL || arqSaida == NULL) {
        imprimeErroArquivo();
        exit(-1);
    }

    criaRegCabecalho(arqSaida);
    createTable(arqEntrada, arqSaida);

    fclose(arqEntrada);
    fclose(arqSaida);
}