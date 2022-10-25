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

//Funcoes Gerais
void readline(char* string);
void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);
void testaErroArquivo(FILE* arquivo);
void verificaStatus(FILE* arquivo);
void atualizaRegCabecalho (FILE* arquivo);

//Funcionalidades
void funcUm(char nomeArqEntrada[], char nomeArqSaida[]);

//Funcionalidade 2
void funcDois(char nomeArqEntrada[]);

//Funcionalidade 3
void funcTres(char nomeArqEntrada[]);
