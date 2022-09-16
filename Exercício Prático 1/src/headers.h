#define NOME_TAMANHO 51
#define SOBRENOME_TAMANHO 51
#define EMAIL_TAMANHO 81
#define NACIONALIDADE_TAMANHO 51

typedef struct {
    char primeiroNome[51];
    char sobreNome[51]; 
    char eMail[81];
    char nacionalidade[51];
    int idade;
} pessoa;

void binarioNaTela(char *nomeArquivoBinario);
void funcionalidade1(FILE* ponteiroArq);
void funcionalidade2(FILE* ponteiroArq);
void funcionalidade3();