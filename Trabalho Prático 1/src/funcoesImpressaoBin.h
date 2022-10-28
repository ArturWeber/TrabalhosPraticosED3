//Header de funcoesImpressaoBin.c

void insereRegistro (FILE* arquivo, registro aux);
regCabecalho inicializaCabecalho(void);
void createTable(FILE* arqEntrada, FILE* arqSaida, regCabecalho* cabecalho);
void imprimeRegistro(registro aux);
void selectFrom(FILE* arqEntrada, regCabecalho cabecalho);
void compactacao(FILE* arqEntrada, FILE* arqSaida, regCabecalho* cabecalho);
