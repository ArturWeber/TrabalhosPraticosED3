//Header de funcoesGerais.c

//Define valores fixos de campo e registro
#define campoMaximo 50
#define linhaMaxima 150
#define tamSiglaPais 2
#define tamUnidadeMedida 1
#define tamRegistro 64

//Apresenta as duas structs utilizadas no projeto
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

void testaErroArquivo(FILE* arquivo);
void leLixo (FILE* arquivo, int compLixo);
regCabecalho recuperaCabecalho (FILE* arquivo);
void verificaStatusLeitura(char status);
registro inicializaRegistro(void);
void binarioNaTela(char *nomeArquivoBinario);
void preenchimentoComSifrao(FILE* arquivo, int tamUsado, int tamMaximo);
void atualizaRegCabecalho (FILE* arquivo, regCabecalho cabecalho);
void manipulaArquivoDuplicata (char* nomeArqOriginal, char* nomeArqTemporario);
void leRegistro(FILE* arquivo, registro* aux);
