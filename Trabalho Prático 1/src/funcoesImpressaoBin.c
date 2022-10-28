#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesGerais.h"

void insereInt(FILE* arquivo, int insercao, int flagTipagem) {
    int intNulo = -1;

    switch (flagTipagem) {
        case 0:
            if (insercao != 0 && insercao != -1) {
                fwrite(&insercao, sizeof(int), 1, arquivo);
            } else {
                fwrite(&intNulo, sizeof(int), 1, arquivo);
            }
            break;
        case 1:
            if (insercao != '\0' && insercao != '$') {
                fwrite(&insercao, sizeof(char), 1, arquivo);
            } else {
                preenchimentoComSifrao(arquivo, 0, tamUnidadeMedida);
            }
            break;
        default:
            break;
    }
}

void insereString(FILE* arquivo, char* insercao, int tamanhoCampo, int isFixo) {
    fwrite(insercao, sizeof(char), strlen(insercao), arquivo);
    if (isFixo) {
        preenchimentoComSifrao(arquivo, strlen(insercao), tamanhoCampo);
    } else {
        fwrite("|", sizeof(char), 1, arquivo);
    }
}

void criaInicioRegistro(FILE* arqSaida) {
    fwrite("0", sizeof(char), 1, arqSaida);

    int inicializar = -1;
    fwrite(&inicializar, sizeof(int), 1, arqSaida);
}

void insereRegistro (FILE* arquivo, registro aux) {
    criaInicioRegistro(arquivo);

    insereInt(arquivo, aux.idConecta, 0);
    insereString(arquivo, aux.siglaPais, tamSiglaPais, 1);
    insereInt(arquivo, aux.idPoPsConectado, 0);
    insereInt(arquivo, aux.unidadeMedida, 1);
    insereInt(arquivo, aux.velocidade, 0);
    insereString(arquivo, aux.nomePoPs, 0, 0);
    insereString(arquivo, aux.nomePais, 0, 0);

    int tamOcupadoRegistro = 22 + strlen(aux.nomePoPs) + strlen(aux.nomePais);
    preenchimentoComSifrao(arquivo, tamOcupadoRegistro, tamRegistro);
}

regCabecalho inicializaCabecalho(void) {
    regCabecalho aux;
    memset(&aux, 0, sizeof(regCabecalho));

    aux.status = '1';
    aux.topo = -1;
    aux.proxRRN = 0;
    aux.nroRegRem = 0;
    aux.nroPagDisco = 1;
    aux.qttCompacta = 0;
    return aux;
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

void imprimeInt(int impressao, char *apresentacao, int flagTipagem) {
    switch (flagTipagem) {
    case 0:
        if (impressao != -1) {
            printf(apresentacao, impressao);
        }
        break;
    case 1:
        if (impressao != '$') {
            printf(apresentacao, impressao);
        }
        break;
    default:
        break;
    }
    
}

void imprimeString(char *impressao, char *apresentacao) {
    if (impressao[0] != '$' && impressao[0] != '\0' && strlen(impressao) > 1) {
        printf(apresentacao, impressao);
    }
}

void imprimeRegistro(registro aux) {
    imprimeInt(aux.idConecta, "Identificador do ponto: %d\n", 0);
    imprimeString(aux.nomePoPs, "Nome do ponto: %s\n");
    imprimeString(aux.nomePais, "Pais de localizacao: %s\n");
    imprimeString(aux.siglaPais, "Sigla do pais: %s\n");
    imprimeInt(aux.idPoPsConectado, "Identificador do ponto conectado: %d\n", 0);
    imprimeInt(aux.velocidade, "Velocidade de transmissao: %d", 0);
    imprimeInt(aux.unidadeMedida, " %cbps\n", 1);
}

void selectFrom(FILE* arqEntrada, regCabecalho cabecalho){
    int encadeamento;
    char removido;

    if (cabecalho.nroPagDisco == 1) {
        printf("Registro inexistente.\n");
        printf("\n");
    }
    
    
    leLixo(arqEntrada, 939);
    for(int rrn = 0; rrn < cabecalho.proxRRN; rrn++){
        fread(&removido, sizeof(char), 1, arqEntrada);
        if(removido == '1'){
            continue;
        }

        registro aux = inicializaRegistro();
        fread(&encadeamento, sizeof(int), 1, arqEntrada);
        fread(&aux.idConecta, sizeof(int), 1, arqEntrada);
        fread(aux.siglaPais, sizeof(char), tamSiglaPais, arqEntrada);
        fread(&aux.idPoPsConectado, sizeof(int), 1, arqEntrada);
        fread(&aux.unidadeMedida, sizeof(char), tamUnidadeMedida, arqEntrada);
        fread(&aux.velocidade, sizeof(int), 1, arqEntrada);

        fscanf(arqEntrada, "%[^|]", aux.nomePoPs);
        leLixo(arqEntrada, 1);
        fscanf(arqEntrada, "%[^|]", aux.nomePais);
        leLixo(arqEntrada, 1);

        imprimeRegistro(aux);
        int comprimentoLixo = 42 - strlen(aux.nomePoPs) - strlen(aux.nomePais);
        leLixo(arqEntrada, comprimentoLixo);

        printf("\n");
    }

    printf("Numero de paginas de disco: %d\n", cabecalho.nroPagDisco);
    printf("\n");

}

void compactacao(FILE* arqEntrada, FILE* arqSaida, regCabecalho* cabecalho){
    int removido;
    int encadeamento;
    int numRegistros = cabecalho->proxRRN;
    for(int rrn = 0; rrn < numRegistros; rrn++){
        fseek(arqEntrada, 960 + (64 * rrn), SEEK_SET);

        fread(&removido, sizeof(char), 1, arqEntrada);
        fread(&encadeamento, sizeof(int), 1, arqEntrada);
        if(removido == '1'){
            cabecalho->proxRRN--;
            cabecalho->nroRegRem--;
            continue;
        }

        registro aux = inicializaRegistro();
        fread(&aux.idConecta, sizeof(int), 1, arqEntrada);
        fread(aux.siglaPais, sizeof(char), tamSiglaPais, arqEntrada);
        fread(&aux.idPoPsConectado, sizeof(int), 1, arqEntrada);
        fread(&aux.unidadeMedida, sizeof(char), tamUnidadeMedida, arqEntrada);
        fread(&aux.velocidade, sizeof(int), 1, arqEntrada);
        fscanf(arqEntrada, "%[^|]", aux.nomePoPs);
        fseek(arqEntrada, 1, SEEK_CUR);
        fscanf(arqEntrada, "%[^|]", aux.nomePais);

        insereRegistro(arqSaida, aux);
    }
    cabecalho->topo = -1;
    cabecalho->status = '1';
    cabecalho->qttCompacta++;
}
