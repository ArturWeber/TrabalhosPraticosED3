#define ordemArvore 5

typedef struct {
    int chave;
    int referencia;
} dado;

typedef struct {
    char folha;
    int nroChavesNo;
    int alturaNo;
    int RRNdoNo;
    int ponteiros[ordemArvore];
    dado dados[ordemArvore - 1];
} registroIndice;

typedef struct {
    char status;
    int noRaiz;
    int nroChavesTotal;
    int alturaArvore;
    int RRNproxNo;
} regCabecalhoIndice;
