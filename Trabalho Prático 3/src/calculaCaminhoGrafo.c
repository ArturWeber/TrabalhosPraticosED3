/************************************************************
 *            Trabalho Prático 3 - SCC0607                   *
 *                                                           *
 *      Nome: Artur Brenner Weber                            *
 *      nUSP: 12675451    Participacao: 100%                 *
 *      Nome: Aruan  Bretas de Oliveira Filho                *
 *      nUSP: 12609731    Participacao: 100%                 *
 *      Data de última atualizacao: 18/12/2022               *
 *      Ambiente de Desenvolv: VSCode 1.74.1                 *
 *                                                           *
 *         Conteudo arquivo geraCalculaGrafo:                *
 *   Funcoes secundarias das funcionalidades 13 e 14         *
*************************************************************/

#include "funcoesGeraisT1.h"
#include "funcoesGeraisT3.h"
#include "calculaCaminhoGrafo.h"

#include <stdio.h>

//verifica qual o vertice com o menor caminho disponivel no momento e o retorna
int idMenorDistDisponivel(Grafo* gr) {
    int idMenor = -1;
    //atribui um valor infinitamente grande
    int distMenor = __INT_MAX__;
    if (gr != NULL) {
        vertice *atual = *gr;
        while (atual != NULL) {
        //verifica se é um vertice o qual não foi marcado ainda
        //se existe caminho para ele
        //e se eh menor que do que a atual menor distancia
            if (atual->cor == BRANCO && atual->distOrigem != -1 && atual->distOrigem < distMenor) {
                distMenor = atual->distOrigem;
                idMenor = atual->dados.idConecta;
            }
            atual = atual->prox;
        }
    }
    return idMenor;
}

//algoritmo responsavel por traçar os pesos das arestas de todas aquelas que estão conectadas com
//o vertice que foi passado como referencia
void dijkstraAlgoritmo(Grafo* gr, int idInicial) {
    //chama funcao que procura o vertice desejado
    vertice* verticeAtual = recuperaVerticeBuscado(gr, idInicial);
    //atribui uma distancia zero, pois nao existe distancia entre ele mesmo
    verticeAtual->distOrigem = 0;
    //atribui como menor distancia ele mesmo no inicio
    int idMenorDist = idInicial;
    do {
        //chama funcao que retorna o vertice atual
        //sendo o que tem a menor distancia do que o anteriormente analisado
        verticeAtual = recuperaVerticeBuscado(gr, idMenorDist);
        vertice* verticeAnalisado;
        int valorAtualizar;
        aresta* arestaAtual = verticeAtual->raizLista;
        while(arestaAtual != NULL) {
            //chama funcao que retorna vertice com conexao com o atual e analisa-o
            verticeAnalisado = recuperaVerticeBuscado(gr, arestaAtual->dados.idPoPsConectado);
            valorAtualizar = arestaAtual->dados.velocidade + verticeAtual->distOrigem;
            //checa se o vertice ja foi analisado em algum momento e caso tenha sido
            //verifica se do vertice atual a distancia eh menor
            if (verticeAnalisado->distOrigem == -1 || (valorAtualizar < verticeAnalisado->distOrigem)) {
                verticeAnalisado->distOrigem = valorAtualizar;
                verticeAnalisado->verticeAnt = idMenorDist;
            }
            arestaAtual = arestaAtual->prox;
        }
        verticeAtual->cor = PRETO;
        //chama funcao que retorna o id do proximo vertice que deve ser analisado
        idMenorDist = idMenorDistDisponivel(gr);
    } while (idMenorDist != -1);
}

//funciona como um memset
//coloca valores nulos para que possamos setar o grafo de formas diferentes para cada entrada
//voltando todos os vertices para branco (não marcado/visitado)
//tirando as distancias e os vertices anteriores quando se trata de menor caminho
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

//funcao que encontra o vertice de destino depois de ser analisado pelo
//algoritmo de dijkstra, e retorna o valor da sua menor distancia partindo de uma origem 
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
    //enquanto houver um vertice anterior para visitar
    while(v->verticeAnt != -1){
        //salva posicao atual no anterior para poder voltar um vertice do caminho indo do destino ate a origem
        posicaoAnt = v->dados.idConecta;
        v = recuperaVerticeBuscado(gr, v->verticeAnt);

        aresta *ar = v->raizLista;
        //encontra naquele vertice o valor do idPoPs para verificar que ha conexao com o anterior
        while(ar != NULL && ar->dados.idPoPsConectado != posicaoAnt){
            ar = ar->prox;
        }
        //caso a velocidade naquele vertice ou seja, peso da aresta for menor, atribui ao novo menor
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
    //vetores que armazenam os valores dos campos os quais queremos encontrar
    //origem e destino
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
        //zerando o grafo para colocarmos valores nulos e desmarcar vertices que possam ter sido marcados
        zeraDistancias(gr);
        //algoritmo que calcula o menor peso ppara chegarmos em um destino partindo de um vertice
        dijkstraAlgoritmo(gr, PoPsOrigem[i]);
        //chama funcao que retorna a Menor velocidade dentro de um menor caminho
        menorVelocidade = encontraMenorVel(gr, PoPsDestino[i]);
        //chamando funcao que retorna a menor distancia de um vertice de origem para um de destino com
        //valores setados anteriormente 
        distancia = retornaDistanciaVertice(gr, PoPsDestino[i]);

        //caso não haja caminho então imprime valor invalido em vai para o proximo
        if (distancia == -1) {
            printf("Fluxo máximo entre %d e %d: %d\n", PoPsOrigem[i], PoPsDestino[i], distancia);
            continue;
        } 

        printf("Fluxo máximo entre %d e %d: %d Mpbs\n", PoPsOrigem[i], PoPsDestino[i], menorVelocidade);        
    }
}

//funcao secundaria da funcionalidade 14, responsavel por chamar
//funcoes que calculam o menor caminho entre uma origem e um destino no grafo
//utilizando o algoritmo de dijkstra
void menorCaminhoGrafo(Grafo* gr) {
    int numeroEntradas; 
    scanf("%d", &numeroEntradas);
    //vetores que armazenam os valores dos campos os quais queremos encontrar
    //origem, parada e destino
    int PoPsOrigem[numeroEntradas], PoPsDestino[numeroEntradas], PoPsParada[numeroEntradas];
    for (int i = 0; i < numeroEntradas; i++) {
        scanf("%d %d %d", &PoPsOrigem[i], &PoPsDestino[i], &PoPsParada[i]);
    }
    //distancia total
    int distancia;
    //distancia da origem ate a parada
    int primDistancia;
    //distancia da parada ate o destino final
    int segDistancia;
    for (int i = 0; i < numeroEntradas; i++) {
        distancia = 0;
        primDistancia = 0;
        segDistancia = 0;

        //Calcula distancia minima da origem para a parada e a soma à distancia minima entre a parada e o destino
        //zerando o grafo para colocarmos valores nulos e desmarcar vertices que possam ter sido marcados
        zeraDistancias(gr);
        //algoritmo que calcula o menor peso ppara chegarmos em um destino partindo de um vertice
        dijkstraAlgoritmo(gr, PoPsOrigem[i]);
        //chamando funcao que retorna a menor distancia de um vertice de origem para um de destino com
        //valores setados anteriormente 
        primDistancia = retornaDistanciaVertice(gr, PoPsParada[i]);

        //caso entre nessa condicao nao existe um caminho da origem para a parada
        //entao imprime valor invalido e passa para o proximo
        if (primDistancia == -1) {
            printf("Comprimento do caminho entre %d e %d parando em %d: %d\n", PoPsOrigem[i], PoPsDestino[i], PoPsParada[i], primDistancia);
            continue;
        } 
        
        //Calcula distancia minima da origem para a parada e a soma à distancia minima entre a parada e o destino
        //zerando o grafo para colocarmos valores nulos e desmarcar vertices que possam ter sido marcados
        zeraDistancias(gr);
        //algoritmo que calcula o menor peso ppara chegarmos em um destino partindo de um vertice
        dijkstraAlgoritmo(gr, PoPsParada[i]);
        //chamando funcao que retorna a menor distancia de um vertice de origem para um de destino com
        //valores setados anteriormente
        segDistancia = retornaDistanciaVertice(gr, PoPsDestino[i]);

        //caso entre nessa condicao nao existe um caminho da parada para o destino
        //entao imprime valor invalido e passa para o proximo
        if (segDistancia == -1) {
            printf("Comprimento do caminho entre %d e %d parando em %d: %d\n", PoPsOrigem[i], PoPsDestino[i], PoPsParada[i], segDistancia);
            continue;
        } 
        //soma-se as duas distancias calculadas caso haja caminho e imprime
        distancia += primDistancia;
        distancia += segDistancia;
        printf("Comprimento do caminho entre %d e %d parando em %d: %dMbps\n", PoPsOrigem[i], PoPsDestino[i], PoPsParada[i], distancia);        
    }
}