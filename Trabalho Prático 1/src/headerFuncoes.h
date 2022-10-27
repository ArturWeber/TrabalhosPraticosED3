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
void readline(char* string);
void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);
void testaErroArquivo(FILE* arquivo);
void verificaStatusLeitura(char status);
void atualizaRegCabecalho (FILE* arquivo, regCabecalho cabecalho);
regCabecalho recuperaCabecalho (FILE* arquivo);
regCabecalho inicializaCabecalho(void);
registro inicializaRegistro(void);
void imprimeInt(int impressao, char *apresentacao, int flagTipagem);
void imprimeString(char *impressao, char *apresentacao);
int descobreCampoBuscado(char* campo);
int temAspas(int indice, int flagFuncionalidade);
int campoEncontrado(int campoBuscado, char* valorCampo, registro aux);
void preenchimentoComSifrao(FILE* arquivo, int tamUsado, int tamMaximo);
void atualizaStatusEscrita (FILE* arquivo);
void insereInt(FILE* arquivo, int insercao, int flagTipagem);
void insereString(FILE* arquivo, char* insercao, int tamanhoCampo, int isFixo);

//Funcionalidades
void funcUm(char *nomeArqEntrada, char *nomeArqSaida); 
void funcDois(char *nomeArqEntrada);
void funcTres(char *nomeArqEntrada);
void funcQuatro(char *nomeArqEntrada);
void funcCinco(char *nomeArqEntrada);