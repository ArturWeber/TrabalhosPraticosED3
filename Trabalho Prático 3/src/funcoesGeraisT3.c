#include "funcoesGeraisT3.h"

/*    Inclui:
    - O tipo de dados "lista"
    - Implementar suas funcoes
*/

#include <stdlib.h>
#include <stdio.h>

Grafo* cria_grafo() {
    Grafo* gr = (Grafo*) malloc(sizeof(Grafo));

    if (gr != NULL) {
        *gr = NULL;
    }
    return gr;
}

// int insere_lista_ordenada(Lista* li, struct aluno a1) {
//     if (li == NULL) {
//         return 0;
//     }

//     Elem *no = (Elem*) malloc(sizeof(Elem));

//     if (no == NULL) {
//         return 0;
//     }

//     no->dados = a1;

//     if (lista_vazia(li)) {
//         no->prox = (*li);
//         *li = no;
//         return 1;
//     }
//     else {
//         //procura onde inserir
//         Elem *atual = *li;
//         Elem *ant = *li;

//         while (atual != NULL && atual->dados.matricula < a1.matricula) {
//             ant = atual;
//             atual = atual->prox;
//         }

//         if (atual == *li) {
//             no->prox = (*li);
//             *li = no;
//         }
//         else {
//             no->prox = ant->prox;
//             ant->prox = no;
//         }

//         return 1;
//     }
// }


void libera_lista(Lista* li) {
    if (li != NULL) {
        aresta* no; 
        while ((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }

        free(li);
    }
}

void libera_grafo(Grafo* gr) {
    if (gr != NULL) {
        vertice* no; 
        while ((*gr) != NULL) {
            no = *gr;
            *gr = (*gr)->prox;
            libera_lista((*gr)->raizLista);
            free(no);
        }

        free(gr);
    }
}
