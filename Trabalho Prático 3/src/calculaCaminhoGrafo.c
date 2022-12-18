/************************************************************
 *            Trabalho Prático 3 - SCC0607                   *
 *                                                           *
 *      Nome: Artur Brenner Weber                            *
 *      nUSP: 12675451    Participacao: 100%                 *
 *      Nome: Aruan  Bretas de Oliveira Filho                *
 *      nUSP: 12609731    Participacao: 100%                 *
 *      Data de última atualizacao: 16/12/2022               *
 *      Ambiente de Desenvolv: VSCode 1.74.1                 *
 *                                                           *
 *         Conteudo arquivo geraCalculaGrafo:                *
 *   Funcoes secundarias das funcionalidades 13 e 14         *
*************************************************************/

#include "funcoesGeraisT1.h"
#include "funcoesGeraisT3.h"
#include "calculaCaminhoGrafo.h"

#include <stdio.h>

int idMenorDistDisponivel(Grafo* gr) {
    int idMenor = -1;
    int distMenor = __INT_MAX__;
    if (gr != NULL) {
        vertice *atual = *gr;
        while (atual != NULL) {
            if (atual->cor == BRANCO && atual->distOrigem != -1 && atual->distOrigem < distMenor) {
                distMenor = atual->distOrigem;
                idMenor = atual->dados.idConecta;
            }
            atual = atual->prox;
        }
    }
    return idMenor;
}

void dijkstraAlgoritmo(Grafo* gr, int idInicial) {
    vertice* verticeAtual = recuperaVerticeBuscado(gr, idInicial);
    verticeAtual->distOrigem = 0;
    int idMenorDist = idInicial;
    do {
        verticeAtual = recuperaVerticeBuscado(gr, idMenorDist);
        vertice* verticeAnalisado;
        int valorAtualizar;
        aresta* arestaAtual = verticeAtual->raizLista;
        while(arestaAtual != NULL) {
            verticeAnalisado = recuperaVerticeBuscado(gr, arestaAtual->dados.idPoPsConectado);
            valorAtualizar = arestaAtual->dados.velocidade + verticeAtual->distOrigem;
            if (verticeAnalisado->distOrigem == -1 || (valorAtualizar < verticeAnalisado->distOrigem)) {
                verticeAnalisado->distOrigem = valorAtualizar;
                //aqui
                verticeAnalisado->verticeAnt = idMenorDist;
            }
            arestaAtual = arestaAtual->prox;
        }
        verticeAtual->cor = PRETO;
        idMenorDist = idMenorDistDisponivel(gr);
    } while (idMenorDist != -1);
}

void zeraDistancias(Grafo* gr) {
    if (gr != NULL) {
        vertice *atual = *gr;
        while (atual != NULL) {
            atual->cor = BRANCO;
            atual->verticeAnt = -1;
            atual->distOrigem = -1;
            atual = atual->prox;
        }
    }
}

int retornaDistanciaVertice(Grafo* gr, int idVertice) {
    if (gr != NULL) {
        vertice *atual = *gr;
        while (atual != NULL && atual->dados.idConecta != idVertice) {
            atual->distOrigem = -1;
            atual = atual->prox;
        }
        if (atual != NULL && atual->dados.idConecta == idVertice) {
            return atual->distOrigem;
        }
    }
    return -1;
}

//funcao que encontra a menor velocidade de uma rota
int encontraMenorVel(Grafo *gr, int destino){
    vertice *v = *gr;
    //estima-se um valor muito alto
    int menorVelocidade = __INT_MAX__;
    v = recuperaVerticeBuscado(gr, destino);
    int posicaoAnt;
    while(v->verticeAnt != -1){
        posicaoAnt = v->dados.idConecta;
        v = recuperaVerticeBuscado(gr, v->verticeAnt);

        aresta *ar = v->raizLista;
        
        while(ar != NULL && ar->dados.idPoPsConectado != posicaoAnt){
            ar = ar->prox;
        }

        if(ar->dados.velocidade < menorVelocidade){
            menorVelocidade = ar->dados.velocidade;
        }
        

    }
    return menorVelocidade;
}

//funcao secundaria da funcionalidade 13, responsavel por
//chamar funções que descubram o menor caminho
//e depois imprimir a menor velocidade de transmissão desse caminho
void fluxoMaximo(Grafo *gr){
    int numeroEntradas; 
    scanf("%d", &numeroEntradas);

    int PoPsOrigem[numeroEntradas], PoPsDestino[numeroEntradas];
    for (int i = 0; i < numeroEntradas; i++) {
        scanf("%d %d", &PoPsOrigem[i], &PoPsDestino[i]);
    }

    int distancia;
    int menorVelocidade;

    //laço que roda n vezes, zerando o as distancias do grafo
    //calculando assim todas as distancias de um vertice de origem
    //e encontrando a menor velocidade presente na menor rota
    for (int i = 0; i < numeroEntradas; i++) {
        distancia = 0;
        //Calcula distancia minima da origem para a parada e a soma à distancia minima entre a parada e o destino
        zeraDistancias(gr);
        dijkstraAlgoritmo(gr, PoPsOrigem[i]);
        //analisa do destino, fazendo o caminho inverso ate a origem para encontrar
        //o menor valor dessa rota
        menorVelocidade = encontraMenorVel(gr, PoPsDestino[i]);
        distancia = retornaDistanciaVertice(gr, PoPsDestino[i]);

        if (distancia == -1) {
            printf("Fluxo máximo entre %d e %d: %d\n", PoPsOrigem[i], PoPsDestino[i], distancia);
            continue;
        } 

        printf("Fluxo máximo entre %d e %d: %d Mpbs\n", PoPsOrigem[i], PoPsDestino[i], menorVelocidade);        
    }
}

void menorCaminhoGrafo(Grafo* gr) {
    int numeroEntradas; 
    scanf("%d", &numeroEntradas);

    int PoPsOrigem[numeroEntradas], PoPsDestino[numeroEntradas], PoPsParada[numeroEntradas];
    for (int i = 0; i < numeroEntradas; i++) {
        scanf("%d %d %d", &PoPsOrigem[i], &PoPsDestino[i], &PoPsParada[i]);
    }

    int distancia;
    int primDistancia;
    int segDistancia;
    for (int i = 0; i < numeroEntradas; i++) {
        distancia = 0;
        primDistancia = 0;
        segDistancia = 0;

        //Calcula distancia minima da origem para a parada e a soma à distancia minima entre a parada e o destino
        zeraDistancias(gr);
        dijkstraAlgoritmo(gr, PoPsOrigem[i]);
        primDistancia = retornaDistanciaVertice(gr, PoPsParada[i]);

        if (primDistancia == -1) {
            printf("Comprimento do caminho entre %d e %d parando em %d: %d\n", PoPsOrigem[i], PoPsDestino[i], PoPsParada[i], primDistancia);
            continue;
        } 

        zeraDistancias(gr);
        dijkstraAlgoritmo(gr, PoPsParada[i]);
        segDistancia = retornaDistanciaVertice(gr, PoPsDestino[i]);
        if (segDistancia == -1) {
            printf("Comprimento do caminho entre %d e %d parando em %d: %d\n", PoPsOrigem[i], PoPsDestino[i], PoPsParada[i], segDistancia);
            continue;
        } 

        distancia += primDistancia;
        distancia += segDistancia;
        printf("Comprimento do caminho entre %d e %d parando em %d: %dMbps\n", PoPsOrigem[i], PoPsDestino[i], PoPsParada[i], distancia);        
    }
}