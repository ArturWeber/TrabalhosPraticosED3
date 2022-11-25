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

    // //VERIFICACOES PARA DEBUGGING
    // printf("\n\n ATUALIZA REGISTRO DE CABECALHO \n");
    // printf("%c \n %d \n %d \n %d \n %d\n", cabecalho.status, cabecalho.noRaiz, cabecalho.nroChavesTotal, cabecalho.alturaArvore, cabecalho.RRNproxNo);
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

registroIndice leRegistroIndice(FILE* arquivo, int rrn){
    fseek(arquivo, (rrn + 1) * 65, SEEK_SET);

    registroIndice noRecuperado;
    memset(&noRecuperado, -1, sizeof(registroIndice));

    fread(&noRecuperado.folha, sizeof(char), 1, arquivo);
	fread(&noRecuperado.nroChavesNo, sizeof(int), 1, arquivo);
	fread(&noRecuperado.alturaNo, sizeof(int), 1, arquivo);
	fread(&noRecuperado.RRNdoNo, sizeof(int), 1, arquivo);
    for (int i = 0; i < ordemArvore - 1; i++) {
	    fread(&noRecuperado.ponteiros[i], sizeof(int), 1, arquivo); 
        fread(&noRecuperado.dados[i].chave, sizeof(int), 1, arquivo);
        fread(&noRecuperado.dados[i].referencia, sizeof(int), 1, arquivo);
    }
    fread(&noRecuperado.ponteiros[ordemArvore - 1], sizeof(int), 1, arquivo);
    return noRecuperado;
}

void salvarNo(FILE *arquivo, registroIndice aux) {
    fseek(arquivo, (aux.RRNdoNo + 1) * 65, SEEK_SET);

    fwrite(&aux.folha, sizeof(char), 1, arquivo);
	fwrite(&aux.nroChavesNo, sizeof(int), 1, arquivo);
	fwrite(&aux.alturaNo, sizeof(int), 1, arquivo);
	fwrite(&aux.RRNdoNo, sizeof(int), 1, arquivo);
    for (int i = 0; i < ordemArvore - 1; i++) {
	    fwrite(&aux.ponteiros[i], sizeof(int), 1, arquivo); 
        fwrite(&aux.dados[i].chave, sizeof(int), 1, arquivo);
        fwrite(&aux.dados[i].referencia, sizeof(int), 1, arquivo);
    }
    fwrite(&aux.ponteiros[ordemArvore - 1], sizeof(int), 1, arquivo);

    // //AJUDA A DEBUGGAR
    // printf("\n\n\nFUNCAO DE SALVAR O NO\n");
    // printf("folha: %c\n", aux.folha);
    // printf("nroChavesNo: %d\n", aux.nroChavesNo);
    // printf("alturaNo: %d\n", aux.alturaNo);
    // printf("RRNdoNo: %d\n", aux.RRNdoNo);
    // for (int i = 0; i < ordemArvore - 1; i++) {
    //     printf("ponteiro%d: %d\n", i + 1, aux.ponteiros[i]);
    //     printf("chave%d: %d\n", i + 1, aux.dados[i].chave);
    //     printf("referencia%d: %d\n", i + 1, aux.dados[i].referencia);
    // }
    // printf("ponteiro%d: %d\n", ordemArvore, aux.ponteiros[ordemArvore - 1]);

}

int posicaoInserir(registroIndice noAtual, int idConecta) {
    int posicaoInserir = 0;
    for (int i = 0; i < noAtual.nroChavesNo; i++) {
        if (noAtual.dados[i].chave < idConecta) {
            posicaoInserir++;
        } else {
            break;
        }
    }
    return posicaoInserir;
}

registroIndice criaNovoNo(char folha, int nroChavesNo, int alturaNo, int RRNdoNo) {
    // cria um novo no do zero
    registroIndice novoNo;
    memset(&novoNo, -1, sizeof(registroIndice));

    novoNo.folha = folha;
    novoNo.nroChavesNo = nroChavesNo;
    novoNo.alturaNo = alturaNo;
    novoNo.RRNdoNo = RRNdoNo;
    for(int i = 0; i < ordemArvore; i++) {
        novoNo.ponteiros[i] = -1;
    }
    for(int i = 0; i < ordemArvore - 1; i++) {
        novoNo.dados[i].chave = -1;
        novoNo.dados[i].referencia = -1;
    }
    return novoNo;
}

registroIndice split(registroIndice* noAtual, dado* dadoInserir, int *ponteiroInserir, regCabecalhoIndice* cabecalhoIndice) {
    //CONTENTS OF PAGE ARE COPIED TO THE WORKING PAGE AND KEY AND RRN ARE INSERTED INTO WORKING PAGE
    int posInserir = posicaoInserir(*noAtual, dadoInserir->chave);
    dado todosDados[ordemArvore];
    int todosPonteiros[ordemArvore + 1];
    todosPonteiros[0] = noAtual->ponteiros[0];
    int j = 0;
    for(int i = 0; i < ordemArvore; i++) {
        if (i == posInserir) {
            todosDados[i] = *dadoInserir;
            todosPonteiros[i + 1] = *ponteiroInserir;
        } else {
            todosDados[i] = noAtual->dados[j];
            todosPonteiros[i + 1] = noAtual->ponteiros[j + 1];
            j++;
        }
    }

    //ALLOCATE AND INITIALIZE A NEW PAGE IN THE B-TREE FILE TO HOLD NEW PAGE
    dado dadoVazio; 
    dadoVazio.chave = -1;
    dadoVazio.referencia = -1;

    int numChavesNo = ordemArvore / 2;
    registroIndice novoNo = criaNovoNo(noAtual->folha, numChavesNo, noAtual->alturaNo, cabecalhoIndice->RRNproxNo);
    cabecalhoIndice->RRNproxNo++;

    noAtual->ponteiros[0] = todosPonteiros[0];
    for (int i = 0; i < numChavesNo; i++) {
        noAtual->dados[i] = todosDados[i];
        noAtual->ponteiros[i + 1] = todosPonteiros[i + 1];
    }
    for (int i = numChavesNo; i < ordemArvore - 1; i++) {
        //limpa os repetidos do noAtual 
        noAtual->dados[i] = dadoVazio;
        noAtual->ponteiros[i + 1] = -1;
    }
    noAtual->nroChavesNo = numChavesNo;
    
    novoNo.ponteiros[0] = todosPonteiros[numChavesNo + 1];
    for (int i = 0; i < numChavesNo; i++) {
        novoNo.dados[i] = todosDados[i + 1 + numChavesNo];
        novoNo.ponteiros[i + 1] = todosPonteiros[i + 2 + numChavesNo];
    }
    novoNo.nroChavesNo = numChavesNo;

    *ponteiroInserir = novoNo.RRNdoNo;
    *dadoInserir = todosDados[numChavesNo];

    return novoNo;
}


void insereRegistroIndice(FILE* arqSaida, dado* dadoInserir, int *ponteiroInserir, regCabecalhoIndice* cabecalhoIndice, int RRNnoAtual) {
    //le o no 
    //read page at RRNnoAtual into noAtual
    registroIndice noAtual = leRegistroIndice(arqSaida, RRNnoAtual);

    //busca onde inserir recursivamente
    if (noAtual.folha == '0') {
        //Continua buscando onde inserir
        int posPonteiro = posicaoInserir(noAtual, dadoInserir->chave);
        int RRNfilho = noAtual.ponteiros[posPonteiro];
        insereRegistroIndice(arqSaida, dadoInserir, ponteiroInserir, cabecalhoIndice, RRNfilho);
    }
    //vai voltando na arvore verificando se tem que inserir elementos promovidos ou nao 
    if (dadoInserir->chave != -1) {
        if (noAtual.nroChavesNo < ordemArvore - 1) {
            //tem espaco
            //procura onde inserir
            int posInserir = posicaoInserir(noAtual, dadoInserir->chave);
            for (int i = noAtual.nroChavesNo; i > posInserir; i--) {
                noAtual.dados[i] = noAtual.dados[i - 1];
                noAtual.ponteiros[i + 1] = noAtual.ponteiros[i];
            }
            noAtual.dados[posInserir] = *dadoInserir;
            noAtual.ponteiros[posInserir + 1] = *ponteiroInserir;
            noAtual.nroChavesNo++;
            //Nao ha mais dados a inserir
            dadoInserir->chave = -1;
            dadoInserir->referencia = -1;
        } else {
            //nao tem mais espaco
            //faz o split e promove!
            registroIndice novoNo = split(&noAtual, dadoInserir, ponteiroInserir, cabecalhoIndice);
            salvarNo(arqSaida, novoNo);
        }
        salvarNo(arqSaida, noAtual);
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

        if (cabecalhoIndice->noRaiz == -1) {
            //se a arvore ainda nao tem nenhum no 
            //cria raiz inicial 
            registroIndice primeiraRaiz = criaNovoNo('1', 0, 1, cabecalhoIndice->RRNproxNo);
            //atualiza cabecalho com novos valores da raiz, atualiza RRNproxNo e aumenta a altura da arvore 
            cabecalhoIndice->noRaiz = cabecalhoIndice->RRNproxNo;
            cabecalhoIndice->RRNproxNo++;
            cabecalhoIndice->alturaArvore++;
            salvarNo(arqSaida, primeiraRaiz);
        }

        dado dadoInserir;
        dadoInserir.chave = registroInserir.idConecta;
        dadoInserir.referencia = rrn;
        int ponteiroInserir = -1;
        insereRegistroIndice(arqSaida, &dadoInserir, &ponteiroInserir, cabecalhoIndice, cabecalhoIndice->noRaiz);

        //SE O DADOINSERIR CONTINUAR SENDO DIFERENTE DE -1 ENTAO TEMOS QUE CRIAR UMA NOVA RAIZ!!!
        //CUIDAR AQUI DO CASO ONDE SPLITA UMA RAIZ!!!
        if (dadoInserir.chave != -1) {
            registroIndice novaRaiz = criaNovoNo('0', 1, cabecalhoIndice->alturaArvore + 1, cabecalhoIndice->RRNproxNo);
            novaRaiz.ponteiros[0] = cabecalhoIndice->noRaiz;
            novaRaiz.dados[0] = dadoInserir;
            novaRaiz.ponteiros[1] = ponteiroInserir;
            salvarNo(arqSaida, novaRaiz);

            cabecalhoIndice->noRaiz = cabecalhoIndice->RRNproxNo;
            cabecalhoIndice->RRNproxNo++;
            cabecalhoIndice->alturaArvore++;
        }
        cabecalhoIndice->nroChavesTotal++;

        //Le lixo do registro para mover ponteiro
        int comprimentoLixo = 42 - strlen(registroInserir.nomePoPs) - strlen(registroInserir.nomePais);
        leLixo(arqEntrada, comprimentoLixo);
    }

    cabecalhoIndice->status = '1';
}
