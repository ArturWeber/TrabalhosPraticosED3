/************************************************************
 *            Trabalho Prático 1 - SCC0607                   *
 *                                                           *
 *      Nome: Artur Brenner Weber                            *
 *      nUSP: 12675451    Participacao: 100%                 *
 *      Nome: Aruan  Bretas de Oliveira Filho                *
 *      nUSP: 12609731    Participacao: 100%                 *
 *      Data de última atualizacao: 28/10/2022               *
 *      Ambiente de Desenvolv: VSCode 1.72.2                 *
 *                                                           *
 *             Conteudo arquivo funcoesBuscaBin:             *
 *   Funcoes gerais utilizadas por todo o codigo, em 5       *
 * ou mais funcionalidades. Seu header inclui as structs     *
 * utilizadas ao longo do projeto.                           *
*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcoesGerais.h"

//Testa erro no arquivo aberto
void testaErroArquivo(FILE* arquivo) {
	if(arquivo == NULL) {
		printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
}

//Le lixo do arquivo para mover ponteiro, evitando fseeks desnecessarios 
void leLixo (FILE* arquivo, int compLixo) {
    char lixo[compLixo];
    fread(lixo, sizeof(char), compLixo, arquivo);
}

//Recupera o cabecalho do arquivo .bin, armazenando em um auxiliar e retornando-o
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

//Verifica se o status do arquivo está como nao corrompido '1'
void verificaStatusLeitura(char status) {
	if(status == '0'){
		printf("Falha no processamento do arquivo.\n");
		exit(0);
	}
}

//Inicializa um registro com valores nulos e retorna-o
registro inicializaRegistro(void){
    registro aux;
    memset(&aux, 0, sizeof(registro));
	return aux;
}


//Funcao fornecida binarioNaTela
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

//Preenche arquivo com sifroes, essencialmente lixo 
void preenchimentoComSifrao(FILE* arquivo, int tamUsado, int tamMaximo){
    //adiciona lixo em bytes não preenchido no campo
    for (int i = 0; i < tamMaximo - tamUsado; i++){
        fwrite("$", sizeof(char), 1, arquivo);
    }
}

//Aplica os valores do cabecalho passado como parametro ao arquivo .bin 
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

//Remove arquivo original e renomeia o novo para o nome do original
void manipulaArquivoDuplicata (char* nomeArqOriginal, char* nomeArqTemporario) {
    remove(nomeArqOriginal);
    rename(nomeArqTemporario, nomeArqOriginal);
}

//le todos os campos de um registro e atribui as variaveis da estrutura registro
void leRegistro(FILE* arquivo, registro* aux){
	fread(&aux->idConecta, sizeof(int), 1, arquivo);
	fread(aux->siglaPais, sizeof(char), tamSiglaPais, arquivo);
	fread(&aux->idPoPsConectado, sizeof(int), 1, arquivo);
	fread(&aux->unidadeMedida, sizeof(char), tamUnidadeMedida, arquivo);
	fread(&aux->velocidade, sizeof(int), 1, arquivo);
	fscanf(arquivo, "%[^|]", aux->nomePoPs);
	leLixo(arquivo, 1);
	fscanf(arquivo, "%[^|]", aux->nomePais);
	leLixo(arquivo, 1);
	return;
}