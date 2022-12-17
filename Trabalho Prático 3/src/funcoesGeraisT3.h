//Cores definidas para utilizacao em funcoes de busca pelo grafo
#define BRANCO 0
#define CINZA 1
#define PRETO 2

//Dados armazenados em cada aresta do grafo
typedef struct {
    int idPoPsConectado;
    int velocidade;
} dadoAresta;

//Estrutura representando a aresta no codigo
typedef struct Aresta {
    dadoAresta dados;

    struct Aresta *prox;
} aresta;

//Estrutura representando a lista de arestas
typedef struct Aresta Lista;

//Dados armazenados em cada vertice do grafo
typedef struct {
    int idConecta; 
    char nomePoPs[campoMaximo];
    char nomePais[campoMaximo];
    char siglaPais[campoMaximo];
} dadoVertice;

//Estrutura representando o vertice do grafo
typedef struct Vertice {
    dadoVertice dados;
    int adicionado;
    int cor;
    int distOrigem;
    Lista* raizLista;

    struct Vertice *prox;
} vertice;

//Estrutura representando a lista de vertices
typedef struct Vertice *Grafo;

//Funcoes de verificacao de erro
void testaAlgumErro(FILE* arquivo);
void verificaStatusArq(char status);

//Funcoes de criacao e manipulacao do grafo
Grafo* cria_grafo();
Lista* cria_lista();
void libera_grafo(Grafo* gr);
int grafo_vazio(Grafo* gr);
int lista_vazia(Lista** li);
vertice* recuperaVerticeBuscado(Grafo* gr, int idBuscado);
