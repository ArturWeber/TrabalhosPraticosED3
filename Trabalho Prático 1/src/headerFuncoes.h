#define campoMaximo 50
#define linhaMaxima 150
#define tamSiglaPais 2
#define tamUnidadeMedida 1
#define tamRegistro 64

typedef struct {
    int idConecta;
    char siglaPais[campoMaximo];
    int idPoPsConectado;
    char unidadeMedida;
    int velocidade;
    char nomePoPs[campoMaximo];
    char nomePais[campoMaximo];
} registro;

typedef struct {
    char status;
    int topo;
    int proxRRN;
    int nroRegRem;
    int nroPagDisco;
    int qttCompacta;
} regCabecalho;

//Funcoes Gerais
void binarioNaTela(char *nomeArquivoBinario); // 1 4 5 6  
void scan_quote_string(char *str); // 3 4 5 
void testaErroArquivo(FILE* arquivo); // 1 2 3 4 5 6 
void verificaStatusLeitura(char status); // 2 3 4 5 6
void atualizaRegCabecalho (FILE* arquivo, regCabecalho cabecalho); // 1 4 5 6 
regCabecalho recuperaCabecalho (FILE* arquivo); // 2 3 4 5 6
regCabecalho inicializaCabecalho(void); // 1 6
registro inicializaRegistro(void); // 1 2 3 4 6
void imprimeRegistro(registro aux); // 2 3
int descobreCampoBuscado(char* campo); // 3 4
int temAspas(int indice, int flagFuncionalidade); // 3 4 5
int campoEncontrado(int campoBuscado, char* valorCampo, registro aux); // 3 4
void atualizaStatusEscrita (FILE* arquivo); // 4 5
void insereRegistro (FILE* arquivo, registro registro); // 1 5 6
void apagaRegistro(FILE* arquivo, int topo); // 4 

//Funcionalidades
void funcUm(char *nomeArqEntrada, char *nomeArqSaida); 
void funcDois(char *nomeArqEntrada);
void funcTres(char *nomeArqEntrada);
void funcQuatro(char *nomeArqEntrada);
void funcCinco(char *nomeArqEntrada);
void funcSeis(char *nomeArqEntrada);