typedef struct {
    char primeiroNome[51];
    char sobreNome[51]; 
    char eMail[81];
    char nacionalidade[51];
    int idade;
} pessoa;

void readline(char* string);
void binarioNaTela(char *nomeArquivoBinario);
void funcionalidade1(FILE* nomeArquivo);
void funcionalidade2();
void funcionalidade3();