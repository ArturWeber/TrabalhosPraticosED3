
void createIndex(FILE* arqEntrada, FILE* arqSaida, regCabecalho cabecalho, regCabecalhoIndice* cabecalhoIndice);
regCabecalhoIndice inicializaCabecalhoIndice(void);
void atualizaRegCabecalhoIndice (FILE* arquivo, regCabecalhoIndice cabecalho);
void engineInsercaoIndice(FILE* arqSaida, regCabecalhoIndice* cabecalhoIndice, registro* registroInserir, dado *dadoInserir, int rrn);
