typedef struct {
    char primeiroNome[50];
    char sobreNome[50]; 
    char eMail[80];
    char nacionalidade[50];
    int idade;
} pessoa;

void readline(char* string);
void binarioNaTela(char *nomeArquivoBinario);
void funcionalidade1(FILE* nomeArquivo);
void funcionalidade2();
void funcionalidade3();