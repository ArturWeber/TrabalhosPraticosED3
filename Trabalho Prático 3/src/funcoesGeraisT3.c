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
 *             Conteudo arquivo funcoesGeraisT3:             *
 *   Funcoes gerais utilizadas por todo o codigo, em 3       *
 * ou mais funcionalidades. Seu header inclui as structs     *
 * utilizadas ao longo do projeto.                           *
*************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "funcoesGeraisT1.h"
#include "funcoesGeraisT3.h"

/*    Inclui:
    - O tipo de dados "lista"
    - Implementar suas funcoes
*/

//Testa erro no arquivo aberto
void testaAlgumErro(FILE* arquivo) {
	if(arquivo == NULL) {
		printf("Falha na execução da funcionalidade.\n");
        exit(0);
    }
}

//Verifica se o status do arquivo está como nao corrompido '1'
void verificaStatusArq(char status) {
	if(status == '0'){
		printf("Falha na execução da funcionalidade.\n");
		exit(0);
	}
}

//Aloca espaco na memoria para a estrutura grafo
Grafo* cria_grafo() {
    Grafo* gr = (Grafo*) malloc(sizeof(Grafo));

    if (gr != NULL) {
        *gr = NULL;
    }
    return gr;
}

//Aloca espaco na memoria para a estrutura lista (usada pelas arestas nesse caso)
Lista* cria_lista() {
    Lista* li = (Lista*) malloc(sizeof(Lista));

    if (li != NULL) {
        li = NULL;
    }
    return li;
}

//Verifica se o grafo esta vazio (sem vertices) para as funcoes de insercao
int grafo_vazio(Grafo* gr) {
    if (gr == NULL) {
        return 1;
    }
    if (*gr == NULL) {
        return 1;
    }
    return 0;
}

//Verifica se a lista de arestas esta vazia para as funcoes de insercao
int lista_vazia(Lista** li) {
    if (li == NULL) {
        return 1;
    }
    if (*li == NULL) {
        return 1;
    }
    return 0;
}

//Libera o espaco alocado em memoria para a lista de arestas
void libera_lista(Lista** li) {
    if (li != NULL) {
        aresta* no;
        while ((*li) != NULL) { 
            no = *li;
            (*li) = (*li)->prox;
            free(no);
        }
    }
}

//Libera o espaco alocado para o grafo em memoria
void libera_grafo(Grafo* gr) {
    if (gr != NULL) {
        vertice* no; 
        while ((*gr) != NULL) {
            no = *gr;
            *gr = (*gr)->prox;
            libera_lista(&no->raizLista);
            free(no);
        }

        free(gr);
    }
}

//Retorna o vertice cujo idConecta foi fornecido dentro do grafo
vertice* recuperaVerticeBuscado(Grafo* gr, int idBuscado) {
    //Vertice atual comeca como vertice inicial, percorrendo o grafo em busca do idBuscado
    vertice* verticeAtual = *gr; 
    while (verticeAtual != NULL && verticeAtual->dados.idConecta < idBuscado) {
        verticeAtual = verticeAtual->prox;
    }
    //Se for encontrado, retorna o vertice, caso contrario, retorna NULL e da mensagem de erro
    if (verticeAtual != NULL && verticeAtual->dados.idConecta == idBuscado) {
        return verticeAtual;
    } else {
        printf("Vertice nao encontrado\n");
        return NULL;
    }
}
