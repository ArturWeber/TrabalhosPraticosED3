//Header de funcoesImpressaoBin.c

void insereInt(FILE* arquivo, int insercao, int flagTipagem);
void insereRegistro (FILE* arquivo, registro aux);
regCabecalho inicializaCabecalho(void);
void createTable(FILE* arqEntrada, FILE* arqSaida, regCabecalho* cabecalho);
void imprimeRegistro(registro aux);
void selectFrom(FILE* arqEntrada, regCabecalho cabecalho);
void compactacao(FILE* arqEntrada, FILE* arqSaida, regCabecalho* cabecalho);
