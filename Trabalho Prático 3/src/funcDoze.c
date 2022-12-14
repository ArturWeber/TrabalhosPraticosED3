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


void calculaCiclos(Grafo* gr) {

    
}