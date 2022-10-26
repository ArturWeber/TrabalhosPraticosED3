#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "headerFuncoes.h"

void readline(char* string) {
    char c = 0;

    do{
        c = (char) getchar();

    } while(c == '\n' || c == '\r' || c == ' ');

    int i = 0;

    do{
        string[i] = c;
        i++;
        c = getchar();
    } while(c != '\n' && c != '\r' && c != ' ');

    string[i]  = '\0';
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

void scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}

void testaErroArquivo(FILE* arquivo) {
	if(arquivo == NULL) {
		printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
}

void verificaStatus(char status) {
	if(status == '0'){
		printf("Falha no processamento do arquivo.\n");
		exit(0);
	}
}

void atualizaRegCabecalho (FILE* arquivo, int topo, int nroRegRem, int qttCompacta) {
	int tamArquivo, proxRRN, nroPagDisco;
	fseek(arquivo, 0L, SEEK_END);
	tamArquivo = ftell(arquivo);
	nroPagDisco = (int) ceil((tamArquivo) / (64.0 * 15.0));
	proxRRN = ((tamArquivo - 960) / 64);

    fseek(arquivo, 0L, SEEK_SET);
	fwrite("1", sizeof(char), 1, arquivo);
    fwrite(&topo, sizeof(int), 1, arquivo);
	fwrite(&proxRRN, sizeof(int), 1, arquivo);
    fwrite(&nroRegRem, sizeof(int), 1, arquivo);
	fwrite(&nroPagDisco, sizeof(int), 1, arquivo);
    fwrite(&qttCompacta, sizeof(int), 1, arquivo);

	return;
}

regCabecalho recuperaCabecalho (FILE* arquivo) {
    fseek(arquivo, 0L, SEEK_SET);
    regCabecalho aux;

    fread(&aux.status, sizeof(char), 1, arquivo);
    fread(&aux.topo, sizeof(int), 1, arquivo);
    fread(&aux.proxRRN, sizeof(int), 1, arquivo);
    fread(&aux.nroRegRem, sizeof(int), 1, arquivo);
    fread(&aux.nroPagDisco, sizeof(int), 1, arquivo);
    fread(&aux.qttCompacta, sizeof(int), 1, arquivo);

    return aux;
}

registro inicializaRegistro(void){
    registro aux;
    memset(&aux, 0, sizeof(registro));
	return aux;
}

void imprimeInt(int impressao, char *apresentacao, int flagTipagem) {
    switch (flagTipagem) {
    case 0:
        if (impressao != -1) {
            printf(apresentacao, impressao);
        }
        break;
    case 1:
        if (impressao != '$') {
            printf(apresentacao, impressao);
        }
        break;
    default:
        break;
    }
    
}

void imprimeString(char *impressao, char *apresentacao) {
    if (impressao[0] != '$' && impressao[0] != '\0' && strlen(impressao) > 1) {
        printf(apresentacao, impressao);
    }
}

int descobreCampoBuscado(char* campo) {
    enum campos{idConecta, siglaPais, idPoPsConectado, unidadeMedida, velocidade, nomePoPs, nomePais};
    if(!strcmp(campo, "idConecta")) {
        return idConecta;
    }
    if(!strcmp(campo, "siglaPais")) {
        return siglaPais;
    }
    if(!strcmp(campo, "idPoPsConectado")) {
        return idPoPsConectado;
    }
    if(!strcmp(campo, "unidadeMedida")) {
        return unidadeMedida;
    }
    if(!strcmp(campo, "velocidade")) {
        return velocidade;
    }
    if(!strcmp(campo, "nomePoPs")) {
        return nomePoPs;
    }
    if(!strcmp(campo, "nomePais")) {
        return nomePais;
    }
    return 7;
}

int temAspas(int indice) {
    if (indice == 0 || indice == 2 || indice == 4) {
        return 0;
    }
    return 1;
}

int campoEncontrado(int campoBuscado, char* valorCampo, registro aux) {
    switch (campoBuscado) {
        case 0:
            if (atoi(valorCampo) == aux.idConecta){
                return 1;
            }
            break;
        case 1:
            if (!strcmp(valorCampo, aux.siglaPais)){
                return 1;
            }
            break;
        case 2:
            if (atoi(valorCampo) == aux.idPoPsConectado){
                return 1;
            }
            break;
        case 3:
            if (valorCampo[0] == aux.unidadeMedida){
                return 1;
            }
            break;
        case 4:
            if (atoi(valorCampo) == aux.velocidade){
                return 1;
            }
            break;
        case 5:
            if (!strcmp(valorCampo, aux.nomePoPs)){
                return 1;
            }
            break;
        case 6:
            if (!strcmp(valorCampo, aux.nomePais)){
                return 1;
            }
            break;
        default:
            break;
    }
    return 0;
}

void preenchimentoComSifrao(FILE* arquivo, int tamUsado, int tamMaximo){
    //adiciona lixo em bytes não preenchido no campo
    for (int i = 0; i < tamMaximo - tamUsado; i++){
        fwrite("$", sizeof(char), 1, arquivo);
    }
}

void atualizaStatusEscrita (FILE* arquivo) {
	fwrite("0", sizeof(char), 1, arquivo);
	fseek(arquivo, 0L, SEEK_SET);
}