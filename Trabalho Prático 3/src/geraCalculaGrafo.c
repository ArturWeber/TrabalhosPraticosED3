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
 *   Funcoes secundarias das funcionalidades 11              *
 * (geraGrafo e imprimeGrafo) e 12 (calculaCiclos)           *
*************************************************************/

#include "funcoesGeraisT1.h"
#include "funcoesGeraisT3.h"
#include "geraCalculaGrafo.h"

#include <string.h>
#include <stdlib.h>

//Funcao insere a aresta em questao no vertice, ehAdicionado vale 1 para 
//Casos usando o idPoPsConectado e vale 0 para casos usando o idConecta
void insereArestaLista (Lista** li, registro aux, int ehAdicionado) {
    int idAdicionar;
    //Define qual id sera utilizado na aresta
    if(ehAdicionado) {
        idAdicionar = aux.idPoPsConectado;
    } else {
        idAdicionar = aux.idConecta;
    }

    //Caso a alocacao da lista de arestas nao tenha sido feita corretamente, retorna
    if (li == NULL) {
        return;
    }

    //Caso haja dados faltantes, nao faz a insercao
    if ((idAdicionar == -1) || (aux.velocidade == -1)) {
        return;
    }

    //Aloca espaco para uma nova aresta e em seguida testa a alocacao
    aresta *no = (aresta*) malloc(sizeof(aresta));
    if (no == NULL) {
        return;
    }

    //Atribui à nova aresta os valores de velocidade e id apropriados 
    int velocidade = aux.velocidade;
    if (aux.unidadeMedida == 'G') {
        velocidade *= 1024;
    }
    no->dados.velocidade = velocidade;
    no->dados.idPoPsConectado = idAdicionar;


    //Procura onde inserir a aresta, em ordem de id crescente
    aresta *atual = *li;
    aresta *ant = *li;
    while (atual != NULL && atual->dados.idPoPsConectado < idAdicionar) {
        ant = atual;
        atual = atual->prox;
    }

    //Se a lista estiver vazia ou a aresta for inserida no inicio, mexe no ponteiro li
    //Caso contrario, so mexe nos ponteiros em volta da regiao de insercao 
    if (atual == *li || lista_vazia(li)){
        no->prox = (*li);
        *li = no;
    } else {
        no->prox = ant->prox;
        ant->prox = no;
    }

    return;
}

//Funcao que insere o vertice no grafo, utilizada para a criacao do grafo
//ehAdicionado utiliza idConecta quando vale 1 e idPoPsConectado quando vale 0
void insereRegistroGrafo(Grafo* gr, registro aux, int ehAdicionado) {
    //Descobre qual id estara sendo utilizada
    int parametroOrdem;
    if (ehAdicionado) {
        parametroOrdem = aux.idConecta;
    } else {
        parametroOrdem = aux.idPoPsConectado;
    }

    //Caso falte dados, nao continua a insercao
    if (parametroOrdem == -1) {
        return;
    }


    //Verifica se o grafo existe
    if (gr == NULL) {
        return;
    }

    //Cria o vertice e o comeco de sua lista a serem inseridos no grafo 
    vertice *no = (vertice*) malloc(sizeof(vertice));
    if (no == NULL) {
        //verifica se alocou
        return;
    }  
    //Aqui estao variaveis de controle de vertice para as outras funcionalidades 
    no->adicionado = ehAdicionado;
    no->cor = BRANCO;
    no->distOrigem = -1;
    //Aqui estao os dados contidos no vertice 
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

    //Procura onde inserir o vertice 
    vertice *atual = *gr;
    vertice *ant = *gr;
    while (atual != NULL && atual->dados.idConecta < parametroOrdem) {
        ant = atual;
        atual = atual->prox;
    }

    //Se ele encontrou um vertice de mesmo id ja contido no grafo, entra no if
    if (atual != NULL && atual->dados.idConecta == parametroOrdem) {
        //Se estivermos tentando inserir ali um vertice incompleto, so colocamos a aresta no vertice que ja existe
        if (!ehAdicionado) {
            insereArestaLista(&atual->raizLista, aux, ehAdicionado);
            return;
        }
        //Caso contrario, insere a aresta no vertice ja existente e em seguida substitui o vertice pelo no 
        no->raizLista = atual->raizLista;   
        insereArestaLista(&no->raizLista, aux, ehAdicionado);
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

//Funcao que gera o grafo a partir do arquivo de entrada
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

//Imprime o grafo conforme a funcionalidade 11
void imprimeGrafo(Grafo *gr) {
    //Caso o grafo exista, o percorre vertice a vertice e aresta a aresta
    if (gr != NULL) {
        vertice *atual = *gr;
        aresta *atualAresta;
        //Percorre grafo vertice a vertice
        while (atual != NULL) {
            atualAresta = atual->raizLista;
            //Percorre grafo aresta a aresta
            while(atualAresta != NULL) {
                //imprime 
                printf("%d %s %s %s %d %dMbps\n", atual->dados.idConecta, atual->dados.nomePoPs, atual->dados.nomePais, atual->dados.siglaPais, atualAresta->dados.idPoPsConectado, atualAresta->dados.velocidade);

                atualAresta = atualAresta->prox;
            }

            atual = atual->prox;
        }
    }
}

//Funcao recursiva que efetua busca em profundidade e conta o numero de ciclos
//Toda vez que a funcao retorna a um vertice que ja eh preto 
void buscaProfundidadeRecursiva(Grafo* gr, int idAtual, int* qtdCiclos) {
    vertice* verticeAtual = recuperaVerticeBuscado(gr, idAtual);
    //Se o vertice ja eh cinza, retorna
    if (verticeAtual->cor == CINZA) {
        return;
    }
    //Se o vertice ja eh preto, conta um ciclo e retorna
    if (verticeAtual->cor == PRETO) {
        (*qtdCiclos)++;
        return;
    }
    //Como vertice foi descoberto, se torna cinza
    verticeAtual->cor = CINZA;
    aresta* arestaAtual = verticeAtual->raizLista;
    //Verifica cada um dos vertices adjacentes ao vertice atual
    while (arestaAtual != NULL) {
        buscaProfundidadeRecursiva(gr, arestaAtual->dados.idPoPsConectado, qtdCiclos);
        arestaAtual = arestaAtual->prox;
    }
    //Depois de verificar todos os vertices adjacentes, atualiza o vertice atual para cinza
    verticeAtual->cor = PRETO;
}

//Funcao que calcula o numero de ciclos em um grafo por meio de uma busca em profundidade
void calculaCiclos(Grafo* gr) {
    //Se o grafo nao existe, retorna
    if (gr == NULL) {
        return;
    }
    vertice *primeiro = *gr;
    int qtdCiclos = 0;
    //Esse while cuida de grafos que sao desconexos pois verifica se algum vertice desconexo nao foi analisado
    while(primeiro != NULL) {
        if (primeiro->cor == BRANCO) {
            buscaProfundidadeRecursiva(gr, primeiro->dados.idConecta, &qtdCiclos);
        } 
        primeiro = primeiro->prox;
    }
    printf("Quantidade de ciclos: %d\n", qtdCiclos);
}