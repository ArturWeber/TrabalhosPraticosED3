/************************************************************
 *            Trabalho Prático 1 - SCC0607                   *
 *                                                           *
 *      Nome: Artur Brenner Weber                            *
 *      nUSP: 12675451    Participacao: 100%                 *
 *      Nome: Aruan  Bretas de Oliveira Filho                *
 *      nUSP: 12609731    Participacao: 100%                 *
 *      Data de última atualizacao: 26/11/2022               *
 *      Ambiente de Desenvolv: VSCode 1.72.2                 *
 *                                                           *
 *             Conteudo arquivo funcoesGeraisT2:             *
 *   Funcoes gerais utilizadas por todo o codigo, em 3       *
 * ou mais funcionalidades. Seu header inclui as structs     *
 * utilizadas ao longo do projeto.                           *
*************************************************************/


#include <stdio.h>
#include <string.h>
#include "funcoesGeraisT2.h"

regCabecalhoIndice recuperaCabecalhoIndice(FILE* arquivo) {
    regCabecalhoIndice aux;
    memset(&aux, 0, sizeof(aux));

    fread(&aux.status, sizeof(char), 1, arquivo);
    fread(&aux.noRaiz, sizeof(int), 1, arquivo);
    fread(&aux.nroChavesTotal, sizeof(int), 1, arquivo);
    fread(&aux.alturaArvore, sizeof(int), 1, arquivo);
    fread(&aux.RRNproxNo, sizeof(int), 1, arquivo);
    
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