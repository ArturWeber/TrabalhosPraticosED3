#include "funcoesGeraisT1.h"
#include "funcoesGeraisT3.h"
#include "funcOnze.h"
#include "funcDoze.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void visitaP(Grafo* g, int u, int *cor){
    cor[u] = AMARELO;
    vertice *v = *g;
    while(v != NULL){
        if(cor[v->dados.idConecta] == BRANCO){
            visitaP(g, v->dados.idConecta, cor);
        }
        v = v->prox;
    }
    cor[u] = VERMELHO;
}

void profundidade(Grafo* g, int numeroReg){
    int cor[numeroReg];

    for(int u = 0; u < numeroReg; u++){
        cor[u] = BRANCO;
    }
    for (int u = 0; u < numeroReg; u++){
        if(cor[u] == BRANCO){
            visitaP(g, u, cor);
        }
    }

}


void calculaCiclos(FILE* arqEntrada, regCabecalho cabecalho){
    //Cria o grafo 
    Grafo* gr = cria_grafo();


    int qttCiclos;
    int encadeamento;
    char removido;

    //Se o numero de paginas de disco for 1 (somente cabecalho), nao ha registro
    if (cabecalho.nroPagDisco == 1) {
        return;
    }
    
    //Le todo o lixo do cabecalho para mover ponteiro e em seguida le registro a registro e imprime
    leLixo(arqEntrada, 939);
    for(int rrn = 0; rrn < cabecalho.proxRRN; rrn++){
        fread(&removido, sizeof(char), 1, arqEntrada);
        //Se for removido nao imprime
        if(removido == '1'){
            leLixo(arqEntrada, 63);
            continue;
        }
        //Senao, le registro e armazena no auxiliar
        registro aux = inicializaRegistro();
        fread(&encadeamento, sizeof(int), 1, arqEntrada);
        //le todos os campos de um registro
        leRegistro(arqEntrada, &aux);

        //Armazena auxiliar no Grafo
        insereRegistroGrafo(gr, aux, 1);
        insereRegistroGrafo(gr, aux, 0);

        //Le lixo do registro para mover ponteiro
        int comprimentoLixo = 42 - strlen(aux.nomePoPs) - strlen(aux.nomePais);
        leLixo(arqEntrada, comprimentoLixo);

    }


    
}