#define campoMaximo 50
#define linhaMaxima 150

typedef struct {
    int idConecta;
    char siglaPais[campoMaximo];
    int idPoPsConectado;
    char unidadeMedida;
    int velocidade;
    char nomePoPs[campoMaximo];
    char nomePais[campoMaximo];
} registro;

//Funcoes Gerais
void readline(char* string);
void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);
void testaErroArquivo(FILE* arquivo);

//Funcionalidades
void funcUm(char nomeArqEntrada[], char nomeArqSaida[]);

//Funcionalidade 2
void funcDois(char nomeArqEntrada[]);
void selectFrom(FILE* arqEntrada);
void selectFromWhere(FILE* arqEntrada);

//Funcionalidade 3
void funcTres(char nomeArqEntrada[]);
