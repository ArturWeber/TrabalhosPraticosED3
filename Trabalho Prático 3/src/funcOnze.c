#include "funcoesGeraisT1.h"
#include "funcoesGeraisT3.h"
#include "funcoesImpressaoBin.h"
#include "funcOnze.h"

#include <string.h>
#include <stdlib.h>

void insereArestaLista (Lista** li, registro aux, int ehAdicionado) {
    int idAdicionar;
    if(ehAdicionado) {
        idAdicionar = aux.idPoPsConectado;
    } else {
        idAdicionar = aux.idConecta;
    }

    if (li == NULL) {
        return;
    }

    if ((idAdicionar == -1) || (aux.velocidade == -1)) {
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
    no->dados.velocidade = velocidade;
    no->dados.idPoPsConectado = idAdicionar;


    //procura onde inserir
    aresta *atual = *li;
    aresta *ant = *li;

    while (atual != NULL && atual->dados.idPoPsConectado < idAdicionar) {
        ant = atual;
        atual = atual->prox;
    }

    if (atual == *li || lista_vazia(li)){
        no->prox = (*li);
        *li = no;
    } else {
        no->prox = ant->prox;
        ant->prox = no;
    }

    return;
}

void insereRegistroGrafo(Grafo* gr, registro aux, int ehAdicionado) {
    int parametroOrdem;
    if (ehAdicionado) {
        parametroOrdem = aux.idConecta;
    } else {
        parametroOrdem = aux.idPoPsConectado;
    }

    if (parametroOrdem == -1) {
        return;
    }

    if (gr == NULL) {
        //verifica se o grafo existe
        return;
    }

    //cria o vertice e sua aresta a serem adicionados ao grafo 
    vertice *no = (vertice*) malloc(sizeof(vertice));
    if (no == NULL) {
        //verifica se alocou
        return;
    }   
    no->adicionado = ehAdicionado;
    no->cor = BRANCO;
    no->distOrigem = -1;
    no->dados.idConecta = parametroOrdem;
    if (ehAdicionado) {
        strcpy(no->dados.nomePais, aux.nomePais);
        strcpy(no->dados.nomePoPs, aux.nomePoPs);
        strcpy(no->dados.siglaPais, aux.siglaPais);
    } else {
        strcpy(no->dados.nomePais, "");
        strcpy(no->dados.nomePoPs, "");
        strcpy(no->dados.siglaPais, "");
    }
    no->raizLista = cria_lista();

    //procura onde inserir
    vertice *atual = *gr;
    vertice *ant = *gr;
    while (atual != NULL && atual->dados.idConecta < parametroOrdem) {
        ant = atual;
        atual = atual->prox;
    }

    if (atual != NULL && atual->dados.idConecta == parametroOrdem) {
        if (!ehAdicionado) {
            //se estivermos tentando inserir um vertice incompleto, so colocamos a aresta e pronto 
            insereArestaLista(&atual->raizLista, aux, ehAdicionado);
            return;
        }

        no->raizLista = atual->raizLista;   
        insereArestaLista(&no->raizLista, aux, ehAdicionado);
        //Caso contrario, substituimos o novo vertice pelo antigo 
        if (atual == *gr || grafo_vazio(gr)) {
            //se o grafo estiver vazio ou adicionar no inicio, ele substitui a raiz
            no->prox = atual->prox;
            *gr = no;
        } else {  
            //se o grafo estiver adicionando no meio, so adiciona normalmanete
            no->prox = atual->prox;
            ant->prox = no;
        }
    } else {
        //Caso o vertice nao existe, adiciona-o
        insereArestaLista(&no->raizLista, aux, ehAdicionado);
        if (atual == *gr || grafo_vazio(gr)) {
            //se o grafo estiver vazio ou adicionar no inicio, ele substitui a raiz
            no->prox = (*gr);
            *gr = no;
        } else {
            //se o grafo estiver adicionando no meio, so adiciona normalmanete
            no->prox = ant->prox;
            ant->prox = no;
        }
    }

    return;
}

void imprimeGrafo(Grafo *gr) {
    if (gr != NULL) {
        vertice *atual = *gr;
        aresta *atualAresta;
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


Grafo* geraGrafo(FILE* arqEntrada, regCabecalho cabecalho) {
    //Cria o grafo 
    Grafo* gr = cria_grafo();

    int encadeamento;
    char removido;

    //Se o numero de paginas de disco for 1 (somente cabecalho), nao ha registro
    if (cabecalho.nroPagDisco == 1) {
        return gr;
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
    
    return gr;
}