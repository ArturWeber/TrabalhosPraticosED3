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
    aux. criaInicioRegistroIndice(arquivo);

    insereInt(arquivo, aux.idConecta, 0);
    insereInt(arquivo, encadeamento, 0);

    int tamOcupadoRegistro = 22 + strlen(aux.nomePoPs) + strlen(aux.nomePais);
    preenchimentoComSifrao(arquivo, tamOcupadoRegistro, tamRegistro);
}

void leRegistroIndice(FILE* arquivo, registroIndice* aux, int rrn){
    fseek(arquivo, (rrn + 1) * 65, SEEK_SET);

	fread(&aux->folha, sizeof(char), 1, arquivo);
	fread(&aux->nroChavesNo, sizeof(int), 1, arquivo);
	fread(&aux->alturaNo, sizeof(char), 1, arquivo);
	fread(&aux->RRNdoNo, sizeof(int), 1, arquivo);
    for (int i = 0; i < ordemArvore - 1; i++) {
	    fread(&aux->ponteiros[i], sizeof(int), 1, arquivo); 
        fread(&aux->dados[i]; sizeof(int), 1, arquivo);
    }
    fread(&aux->ponteiros[ordemArvore - 1], sizeof(int), 1, arquivo);
	return;
}

void salvarNo(FILE *arquivo, registroIndice* aux, int rrn) {
    fseek(arquivo, (rrn + 1) * 65, SEEK_SET);

    fwrite(&aux->folha, sizeof(char), 1, arquivo);
	fwrite(&aux->nroChavesNo, sizeof(int), 1, arquivo);
	fwrite(&aux->alturaNo, sizeof(char), 1, arquivo);
	fwrite(&aux->RRNdoNo, sizeof(int), 1, arquivo);
    for (int i = 0; i < ordemArvore - 1; i++) {
	    fwrite(&aux->ponteiros[i], sizeof(int), 1, arquivo); 
        fwrite(&aux->dados[i]; sizeof(int), 1, arquivo);
    }
    fwrite(&aux->ponteiros[ordemArvore - 1], sizeof(int), 1, arquivo);
	return;
}

int posicaoInserir(registroIndice noAtual, int idConecta) {
    int posicaoInserir = 0;
    for (int i = 0; i < noAtual.nroChavesNo; i++) {
        if (noAtual.dados[i].chave < idConecta) {
            posPonteiro++;
        } else {
            break;
        }
    }
}

void criaNovoNo() {
// cria um novo no do zero
}

void insereRegistroIndice (FILE* arqSaida, int idConecta, int referencia, regCabecalhoIndice* cabecalhoIndice, int RRNnoAtual) {
    //PROCESSO DE BUSCAR ONDE INSERIR
    if (RRNnoAtual == -1) {
        //nao tem nenhum no 
        //criar no raiz
        return; 
    }
    //le no 
    registroIndice noAtual;
    leRegistroIndice(arqSaida, &noAtual, RRNnoAtual);
    //se for folha ele insere
    if (noAtual.folha == '0') {
        //procura o filho 
        int posPonteiro = posicaoInserir(noAtual, idConecta);
        int RRNfilho = noAtual.ponteiros[posPonteiro];
        insereRegistroIndice(arqSaida, idConecta, referencia, cabecalhoIndice, RRNfilho);
    } else {
        if (noAtual.nroChavesNo < ordemArvore - 1) {
            //tem espaco
            //procura onde inserir 
            int posInserir = posicaoInserir(noAtual, idConecta);
            for (int i = noAtual.nroChavesNo; i > posInserir; i--) {
                noAtual.dados[i] = noAtual.dados[i - 1];
            }
            noAtual.dados[posInserir].chave = idConecta;
            noAtual.dados[posInserir].referencia = referencia;
            cabecalhoIndice->nroChavesTotal++;
            noAtual.nroChavesNo++;
            salvarNo(arqSaida, noAtual, RRNnoAtual);
        } else {
            //nao tem mais espaco
            //faz o split e promove!
        }
    }
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
        registro registroInserir = inicializaRegistro();
        fread(&encadeamento, sizeof(int), 1, arqEntrada);
        //le todos os campos de um registro
        leRegistro(arqEntrada, &registroInserir);

        int idConecta = registroInserir.idConecta;
        insereRegistroIndice(arqSaida, idConecta, rrn, &cabecalhoIndice, cabecalhoIndice->noRaiz);

        //Le lixo do registro para mover ponteiro
        int comprimentoLixo = 42 - strlen(aux.nomePoPs) - strlen(aux.nomePais);
        leLixo(arqEntrada, comprimentoLixo);
    }

}