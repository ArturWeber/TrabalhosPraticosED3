#include "funcoesGeraisT1.h"
#include "funcoesGeraisT3.h"
#include "funcOnze.h"
#include "funcDoze.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void buscaProfundidadeRecursiva(Grafo* gr, int idAtual, int* qtdCiclos) {
    vertice* verticeAtual = recuperaVerticeBuscado(gr, idAtual);
    if (verticeAtual->cor == CINZA) {
        return;
    }
    if (verticeAtual->cor == PRETO) {
        (*qtdCiclos)++;
        return;
    }
    verticeAtual->cor = CINZA;
    aresta* arestaAtual = verticeAtual->raizLista;
    while (arestaAtual != NULL) {
        buscaProfundidadeRecursiva(gr, arestaAtual->dados.idPoPsConectado, qtdCiclos);
        arestaAtual = arestaAtual->prox;
    }
    verticeAtual->cor = PRETO;
}

void calculaCiclos(Grafo* gr) {
    if (gr == NULL) {
        return;
    }
    vertice *primeiro = *gr;
    int qtdCiclos = 0;
    //Esse while cuida de grafos que sao desconexos 
    while(primeiro != NULL) {
        if (primeiro->cor == BRANCO) {
            buscaProfundidadeRecursiva(gr, primeiro->dados.idConecta, &qtdCiclos);
        } 
        primeiro = primeiro->prox;
    }
    printf("Quantidade de ciclos: %d\n", qtdCiclos);
}