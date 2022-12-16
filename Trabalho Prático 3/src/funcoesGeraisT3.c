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

Grafo* cria_grafo() {
    Grafo* gr = (Grafo*) malloc(sizeof(Grafo));

    if (gr != NULL) {
        *gr = NULL;
    }
    return gr;
}

Lista* cria_lista() {
    Lista* li = (Lista*) malloc(sizeof(Lista));

    if (li != NULL) {
        li = NULL;
    }
    return li;
}

int grafo_vazio(Grafo* gr) {
    if (gr == NULL) {
        return 1;
    }
    if (*gr == NULL) {
        return 1;
    }
    return 0;
}

int lista_vazia(Lista** li) {
    if (li == NULL) {
        return 1;
    }
    if (*li == NULL) {
        return 1;
    }
    return 0;
}

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

vertice* recuperaVerticeBuscado(Grafo* gr, int idBuscado) {
    vertice* verticeAtual = *gr; 
    while (verticeAtual != NULL && verticeAtual->dados.idConecta < idBuscado) {
        verticeAtual = verticeAtual->prox;
    }
    if (verticeAtual != NULL && verticeAtual->dados.idConecta == idBuscado) {
        return verticeAtual;
    } else {
        printf("Vertice nao encontrado\n");
        return NULL;
    }
} 