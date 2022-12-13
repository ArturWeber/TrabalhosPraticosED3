#include "funcoesGeraisT1.h"
#include "funcoesGeraisT3.h"
#include "funcoesImpressaoBin.h"
#include "funcOnze.h"

#include <string.h>
#include <stdlib.h>

void insereArestaLista (Lista** li, registro aux) {
    if (li == NULL) {
        return;
    }

    if ((aux.idPoPsConectado == -1) || (aux.velocidade == -1)) {
        return;
    }

    aresta *no = (aresta*) malloc(sizeof(aresta));
    if (no == NULL) {
        return;
    }

    int velocidade = aux.velocidade;
    if (aux.unidadeMedida == 'G') {
        velocidade *= 1024;
    }

    no->dados.idPoPsConectado = aux.idPoPsConectado;
    no->dados.velocidade = velocidade;

    if (lista_vazia(li)) {
        no->prox = *li;
        *li = no;
        return;
    } else {
        //procura onde inserir
        aresta *atual = *li;
        aresta *ant = *li;

        while (atual != NULL && atual->dados.idPoPsConectado < aux.idPoPsConectado) {
            ant = atual;
            atual = atual->prox;
        }

        if (atual == *li) {
            no->prox = *li;
            *li = no;
        }
        else {
            no->prox = ant->prox;
            ant->prox = no;
        }

        return;
    }


}

void insereRegistroGrafo(Grafo* gr, registro aux) {
    
    if (gr == NULL) {
        return;
    }

    vertice *no = (vertice*) malloc(sizeof(vertice));

    if (no == NULL) {
        return;
    }

    
    if (grafo_vazio(gr)) {
        no->adicionado = 1;
        no->dados.idConecta = aux.idConecta;
        strcpy(no->dados.nomePais, aux.nomePais);
        strcpy(no->dados.nomePoPs, aux.nomePoPs);
        strcpy(no->dados.siglaPais, aux.siglaPais);
        printf("%d\n", no->dados.idConecta);
        insereArestaLista(&no->raizLista, aux);
        no->prox = (*gr);
        *gr = no;
        return;
    } else {
        //procura onde inserir
        vertice *atual = *gr;
        vertice *ant = *gr;

        while (atual != NULL && atual->dados.idConecta < aux.idConecta) {
            ant = atual;
            atual = atual->prox;
        }

        if (atual != NULL && atual->dados.idConecta == aux.idConecta) {
            insereArestaLista(&atual->raizLista, aux);
        } else {
            no->adicionado = 1;
            no->dados.idConecta = aux.idConecta;
            strcpy(no->dados.nomePais, aux.nomePais);
            strcpy(no->dados.nomePoPs, aux.nomePoPs);
            strcpy(no->dados.siglaPais, aux.siglaPais);
            no->raizLista = cria_lista();
            insereArestaLista(&no->raizLista, aux);
        }

        if (atual == *gr) {
            no->prox = (*gr);
            *gr = no;
        }
        else {
            no->prox = ant->prox;
            ant->prox = no;
        }

        return;
    }
}

void imprimeGrafo(Grafo *gr) {
    if (gr != NULL) {
        vertice *atual = *gr;
        Lista *atualAresta;
        while (atual != NULL) {
            atualAresta = atual->raizLista;
            while(atualAresta != NULL) {
                //imprime 
                printf("%d %s %s %s %d %dMbps\n", atual->dados.idConecta, atual->dados.nomePoPs, atual->dados.nomePais, atual->dados.siglaPais, atualAresta->dados.idPoPsConectado, atualAresta->dados.velocidade);

                atualAresta = atualAresta->prox;
            }

            atual = atual->prox;
        }
    }
}

void geraImprimeGrafo(FILE* arqEntrada, regCabecalho cabecalho) {
    //Cria o grafo 
    Grafo* gr = cria_grafo();

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
        insereRegistroGrafo(gr, aux);

        //Le lixo do registro para mover ponteiro
        int comprimentoLixo = 42 - strlen(aux.nomePoPs) - strlen(aux.nomePais);
        leLixo(arqEntrada, comprimentoLixo);

    }
    
    imprimeGrafo(gr);
}