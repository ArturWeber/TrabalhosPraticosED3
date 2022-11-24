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

void salvarNo(FILE *arquivo, registroIndice aux) {
    fseek(arquivo, (aux.RRNdoNo + 1) * 65, SEEK_SET);

    fwrite(&aux.folha, sizeof(char), 1, arquivo);
	fwrite(&aux.nroChavesNo, sizeof(int), 1, arquivo);
	fwrite(&aux.alturaNo, sizeof(char), 1, arquivo);
	fwrite(&aux.RRNdoNo, sizeof(int), 1, arquivo);
    for (int i = 0; i < ordemArvore - 1; i++) {
	    fwrite(&aux.ponteiros[i], sizeof(int), 1, arquivo); 
        fwrite(&aux.dados[i]; sizeof(int), 1, arquivo);
    }
    fwrite(&aux.ponteiros[ordemArvore - 1], sizeof(int), 1, arquivo);
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

registroIndice criaNovoNo(char folha, int nroChavesNo, int alturaNo, int RRNdoNo, int ponteiros[], dado dados[]) {
    // cria um novo no do zero
    registroIndice novoNo;
    novoNo.folha = folha;
    novoNo.nroChavesNo = nroChavesNo;
    novoNo.alturaNo = alturaNo;
    novoNo.RRNdoNo = RRNdoNo;
    for(int i = 0; i < ordemArvore; i++) {
        novoNo.ponteiros[i] = ponteiros[i];
    }
    for(int i = 0; i < ordemArvore - 1; i++) {
        novoNo.dados[i] = dados[i];
    }
    return novoNo;
}

void insereRegistroIndice(FILE* arqSaida, dado* dadoInserir, int ponteiroInserir, regCabecalhoIndice* cabecalhoIndice, int RRNnoAtual) {
    // se nao houver promocao entao para de mexer
    if (dadoInserir->chave == -1) {
        return;
    }

    if (RRNnoAtual == -1) {
        //nao tem nenhum no 
        //criar no raiz
        int ponteiros[ordemArvore];
        for (int i = 0; i < ordemArvore; i++) {
            ponteiros[i] = -1;
        }
        dado dados[ordemArvore - 1];
        for (int i = 0; i < ordemArvore - 1; i++) {
            dados[i].chave = 0;
            dados[i].referencia = -1;
        }
        registroIndice novoNo = criarNovoNo('1', 0, 1, cabecalhoIndice->RRNproxNo, ponteiros, dados);
        cabecalhoIndice->noRaiz = cabecalhoIndice->RRNproxNo;
        cabecalhoIndice->RRNproxNo++;
        cabecalhoIndice->alturaArvore++;
        salvarNo(arqSaida, novoNo);
        RRNnoAtual = 0;
    }

    //le o no 
    registroIndice noAtual;
    leRegistroIndice(arqSaida, &noAtual, RRNnoAtual);

    //se nao for no folha
    if (noAtual.folha == '0') {
        //Continua buscando onde inserir
        int posPonteiro = posicaoInserir(noAtual, dadoInserir->chave);
        int RRNfilho = noAtual.ponteiros[posPonteiro];
        insereRegistroIndice(arqSaida, dadoInserir, cabecalhoIndice, RRNfilho);
    } else {
        if (noAtual.nroChavesNo < ordemArvore - 1) {
            //tem espaco
            //procura onde inserir 
            int posInserir = posicaoInserir(noAtual, dadoInserir->chave);
            for (int i = noAtual.nroChavesNo; i > posInserir; i--) {
                noAtual.dados[i] = noAtual.dados[i - 1];
                noAtual.ponteiros[i + 1] = noAtual.ponteiros[i];
            }
            noAtual.dados[posInserir] = *dadoInserir;
            noAtual.ponteiros[posInserir + 1] = ponteiroInserir;
            cabecalhoIndice->nroChavesTotal++;
            noAtual.nroChavesNo++;
            salvarNo(arqSaida, noAtual);
            //Nao ha mais dados a inserir
            dadoInserir->chave = -1;
        } else {
            //nao tem mais espaco
            //faz o split e promove!
            // o dadoInserir eh o promovido
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

        dado dadoInserir;
        dadoInserir.chave = registroInserir.idConecta;
        dadoInserir.referencia = rrn;
        insereRegistroIndice(arqSaida, &dadoInserir, -1, &cabecalhoIndice, cabecalhoIndice->noRaiz);

        //Le lixo do registro para mover ponteiro
        int comprimentoLixo = 42 - strlen(aux.nomePoPs) - strlen(aux.nomePais);
        leLixo(arqEntrada, comprimentoLixo);
    }

    cabecalhoIndice->status = '1';

}

//Ler o livro 
//Testar insercao para ate 4 registros (idconecta)