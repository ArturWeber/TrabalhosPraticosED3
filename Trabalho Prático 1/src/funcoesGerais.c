#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funcoesGerais.h"

void testaErroArquivo(FILE* arquivo) {
	if(arquivo == NULL) {
		printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
}

void leLixo (FILE* arquivo, int compLixo) {
    char lixo[compLixo];
    fread(lixo, sizeof(char), compLixo, arquivo);
}

regCabecalho recuperaCabecalho (FILE* arquivo) {
    regCabecalho aux;
    memset(&aux, 0, sizeof(aux));

    fread(&aux.status, sizeof(char), 1, arquivo);
    fread(&aux.topo, sizeof(int), 1, arquivo);
    fread(&aux.proxRRN, sizeof(int), 1, arquivo);
    fread(&aux.nroRegRem, sizeof(int), 1, arquivo);
    fread(&aux.nroPagDisco, sizeof(int), 1, arquivo);
    fread(&aux.qttCompacta, sizeof(int), 1, arquivo);
    
    return aux;
}

void verificaStatusLeitura(char status) {
	if(status == '0'){
		printf("Falha no processamento do arquivo.\n");
		exit(0);
	}
}

registro inicializaRegistro(void){
    registro aux;
    memset(&aux, 0, sizeof(registro));
	return aux;
}

void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}

void preenchimentoComSifrao(FILE* arquivo, int tamUsado, int tamMaximo){
    //adiciona lixo em bytes não preenchido no campo
    for (int i = 0; i < tamMaximo - tamUsado; i++){
        fwrite("$", sizeof(char), 1, arquivo);
    }
}

void atualizaRegCabecalho (FILE* arquivo, regCabecalho cabecalho) {
	int nroPagDisco;
	nroPagDisco = (int) (ceil((cabecalho.proxRRN) / 15.0) + 1);

    fseek(arquivo, 0L, SEEK_SET);
	fwrite(&cabecalho.status, sizeof(char), 1, arquivo);
    fwrite(&cabecalho.topo, sizeof(int), 1, arquivo);
	fwrite(&cabecalho.proxRRN, sizeof(int), 1, arquivo);
    fwrite(&cabecalho.nroRegRem, sizeof(int), 1, arquivo);
	fwrite(&nroPagDisco, sizeof(int), 1, arquivo);
    fwrite(&cabecalho.qttCompacta, sizeof(int), 1, arquivo);

    preenchimentoComSifrao(arquivo, 21, 960);
	return;
}

void manipulaArquivoDuplicata (char* nomeArqOriginal, char* nomeArqTemporario) {
    remove(nomeArqOriginal);
    rename(nomeArqTemporario, nomeArqOriginal);
}
