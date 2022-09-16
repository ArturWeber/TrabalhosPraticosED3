#define NOME_TAMANHO 51
#define SOBRENOME_TAMANHO 51
#define EMAIL_TAMANHO 81
#define NACIONALIDADE_TAMANHO 51

typedef struct {
    char primeiroNome[NOME_TAMANHO];
    char sobreNome[SOBRENOME_TAMANHO]; 
    char eMail[EMAIL_TAMANHO];
    char nacionalidade[NACIONALIDADE_TAMANHO];
    int idade;
} pessoa;

void binarioNaTela(char *nomeArquivoBinario);
void funcionalidade1(FILE* ponteiroArq);
void funcionalidade2(FILE* ponteiroArq);
void funcionalidade3(FILE* ponteiroArq);