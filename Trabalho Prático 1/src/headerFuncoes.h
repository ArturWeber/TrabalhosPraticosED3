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


//Fornecidas
void readline(char* string);
void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);
void imprimeErroArquivo();

//funcionalidades
void funcUm(char nomeArqEntrada[], char nomeArqSaida[]);
void funcDois(char nomeArqEntrada[]);
void funcTres(char nomeArqEntrada[]);

//createTable
void TratamentoDeRegistro(FILE* arqSaida, int TamUsado);
void criaRegCabecalho(FILE* arq);
void createTable(FILE* arqEntrada, FILE* arqSaida);

//selectFrom
void selectFrom(FILE* arqEntrada);
void selectFromWhere(FILE* arqEntrada);
