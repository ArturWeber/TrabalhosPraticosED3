/*    Inclui:
    - Os prototipos das funcoes
    - O tipo de dado armazenado na lista
    - O ponteiro "lista"
*/
#define BRANCO 0
#define CINZA 1
#define PRETO 2

typedef struct {
    int idPoPsConectado;
    int velocidade;
} dadoAresta;

typedef struct Aresta {
    dadoAresta dados;

    struct Aresta *prox;
} aresta;

typedef struct Aresta Lista;

typedef struct {
    int idConecta; 
    char nomePoPs[campoMaximo];
    char nomePais[campoMaximo];
    char siglaPais[campoMaximo];
} dadoVertice;

typedef struct Vertice {
    dadoVertice dados;
    int adicionado;
    int cor;
    int distOrigem;
    Lista* raizLista;

    struct Vertice *prox;
} vertice;

typedef struct Vertice *Grafo;

void testaAlgumErro(FILE* arquivo);
void verificaStatusArq(char status);

Grafo* cria_grafo();
Lista* cria_lista();

void libera_grafo(Grafo* gr);
int grafo_vazio(Grafo* gr);
int lista_vazia(Lista** li);
vertice* recuperaVerticeBuscado(Grafo* gr, int idBuscado);
