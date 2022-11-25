//Header de funcoesBuscaBin.c

void selectFromWhere(FILE* arqEntrada, regCabecalho aux);
void atualizaStatusEscrita (FILE* arquivo);
void remocaoLogica(FILE* arqEntrada, regCabecalho* cabecalho);
void insertInto(FILE* arquivo, regCabecalho* cabecalho);
int descobreCampoBuscado(char* campo);
int temAspas(int indice, int flagFuncionalidade);
void scan_quote_string(char *str);
int campoEncontrado(int campoBuscado, char* valorCampo, registro aux);
void leCamposDeBusca(char (*descricaoCampo)[campoMaximo], char (*valorCampoBuscado)[campoMaximo], int indiceCampoBuscado[], int numBuscas);