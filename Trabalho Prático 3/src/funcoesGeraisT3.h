/*    Inclui:
    - Os prototipos das funcoes
    - O tipo de dado armazenado na lista
    - O ponteiro "lista"
*/

typedef struct {
    int idPoPsConectado;
    int velocidade;
} dadoAresta;

struct Aresta {
    dadoAresta dados;

    struct Aresta *prox;
};

typedef struct Aresta aresta; 
typedef struct Aresta Lista;

typedef struct {
    int idConecta; 
    char nomePoPs[campoMaximo];
    char nomePais[campoMaximo];
    char siglaPais[campoMaximo];
} dadoVertice;

struct Vertice {
    dadoVertice dados;
    int adicionado;
    Lista* raizLista;

    struct Vertice *prox;
};

typedef struct Vertice vertice;
typedef struct Vertice *Grafo;

Grafo* cria_grafo();
Lista* cria_lista();

void libera_grafo(Grafo* gr);
int grafo_vazio(Grafo* gr);
int lista_vazia(Lista** li);
