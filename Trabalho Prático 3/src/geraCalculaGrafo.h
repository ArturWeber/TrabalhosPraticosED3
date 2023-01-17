#include "stdio.h"

void imprimeGrafo(Grafo *gr);
void insereRegistroGrafo(Grafo* gr, registro aux, int ehAdicionado);
Grafo* geraGrafo(FILE* arqEntrada, regCabecalho cabecalho);
void calculaCiclos(Grafo* gr);