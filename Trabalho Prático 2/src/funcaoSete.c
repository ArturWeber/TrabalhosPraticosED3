#include <stdio.h>
#include <string.h>
#include "funcoesGeraisT1.h"
#include "funcoesGeraisT2.h"
#include "funcaoSete.h"
#include "funcoesImpressaoBin.h"


void atualizaRegCabecalhoIndice (FILE* arquivo, regCabecalhoIndice cabecalho) {

    fseek(arquivo, 0L, SEEK_SET);
	fwrite(&cabecalho.status, sizeof(char), 1, arquivo);
    fwrite(&cabecalho.noRaiz, sizeof(int), 1, arquivo);
	fwrite(&cabecalho.nroChavesTotal, sizeof(int), 1, arquivo);
    fwrite(&cabecalho.alturaArvore, sizeof(int), 1, arquivo);
    fwrite(&cabecalho.RRNproxNo, sizeof(int), 1, arquivo);

    preenchimentoComSifrao(arquivo, 17, 65);
	return;
}

regCabecalhoIndice inicializaCabecalhoIndice(void) {
    regCabecalhoIndice aux;
    memset(&aux, 0, sizeof(regCabecalhoIndice));

    aux.status = '0';
    aux.noRaiz = -1;
    aux.nroChavesTotal = 0;
    aux.alturaArvore = 0;
    aux.RRNproxNo = 0;
    return aux;
}

void criaInicioRegistroIndice(FILE* arqSaida) {
    fwrite("0", sizeof(char), 1, arqSaida);

    int inicializar = -1;
    fwrite(&inicializar, sizeof(int), 1, arqSaida);
}

void insereRegistroIndice (FILE* arquivo, registro aux, int encadeamento) {
    criaInicioRegistroIndice(arquivo);

    insereInt(arquivo, aux.idConecta, 0);
    insereInt(arquivo, encadeamento, 0);

    int tamOcupadoRegistro = 22 + strlen(aux.nomePoPs) + strlen(aux.nomePais);
    preenchimentoComSifrao(arquivo, tamOcupadoRegistro, tamRegistro);
}

void createIndex(FILE* arqEntrada, FILE* arqSaida, regCabecalho cabecalho, regCabecalhoIndice* cabecalhoIndice){
    int encadeamento;
    char removido;
    
    //Le todo o lixo do cabecalho para mover ponteiro e em seguida le registro a registro e imprime
    leLixo(arqEntrada, 939);
    for(int rrn = 0; rrn < cabecalho.proxRRN; rrn++){

        fread(&removido, sizeof(char), 1, arqEntrada);
        //Se for removido nao adiciona ao indice
        if(removido == '1'){
            leLixo(arqEntrada, 63);
            continue;
        }

        //Senao, le registro e armazena no auxiliar
        registro aux = inicializaRegistro();
        fread(&encadeamento, sizeof(int), 1, arqEntrada);
        //le todos os campos de um registro
        leRegistro(arqEntrada, &aux);

        insereRegistroIndice(arqSaida, aux, encadeamento);

        //Le lixo do registro para mover ponteiro
        int comprimentoLixo = 42 - strlen(aux.nomePoPs) - strlen(aux.nomePais);
        leLixo(arqEntrada, comprimentoLixo);
    }

}