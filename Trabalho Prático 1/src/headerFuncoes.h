#define campoMaximo 50
#define linhaMaxima 100

typedef struct {
    int idConecta;
    char siglaPais[campoMaximo];
    int idPoPsConectado;
    char unidadeMedida[2];
    int velocidade;
    char nomePoPs[campoMaximo];
    char nomePais[campoMaximo];
} registro;

void readline(char* string);
void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);
void imprimeErroArquivo();

void funcUm(char nomeArqEntrada[], char nomeArqSaida[]);
void criaRegCabecalho(FILE* arq);
void createTable(FILE* arqEntrada, FILE* arqSaida);
