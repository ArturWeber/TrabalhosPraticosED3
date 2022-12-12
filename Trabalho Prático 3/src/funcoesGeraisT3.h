/*    Inclui:
    - Os prototipos das funcoes
    - O tipo de dado armazenado na lista
    - O ponteiro "lista"
*/

typedef struct {
    int idPoPsConectado;
    int velocidade;
} dadoAresta;

typedef struct Aresta {
    dadoAresta dados;

    struct Aresta *prox;
} aresta;

typedef aresta *Lista;

typedef struct {
    int idConecta; 
    char nomePoPs[campoMaximo];
    char nomePais[campoMaximo];
    char siglaPais[campoMaximo];
} dadoVertice;

typedef struct Vertice {
    dadoVertice dados;
    int adicionado;
    Lista* raizLista;

    struct Vertice *prox;
} vertice;

typedef vertice *Grafo;

Grafo* cria_grafo();

void libera_grafo(Grafo* ve);
