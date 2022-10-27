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

void verificaStatusLeitura(char status) {
	if(status == '0'){
		printf("Falha no processamento do arquivo.\n");
		exit(0);
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

regCabecalho inicializaCabecalho(void) {
    regCabecalho aux;
    memset(&aux, 0, sizeof(regCabecalho));

    aux.status = '1';
    aux.topo = -1;
    aux.proxRRN = 0;
    aux.nroRegRem = 0;
    aux.nroPagDisco = 1;
    aux.qttCompacta = 0;
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

int temAspas(int indice, int flagFuncionalidade) {
    if (flagFuncionalidade == 0) {
        if (indice == 0 || indice == 2 || indice == 4) {
            return 0;
        }
        return 1;
    } else if (flagFuncionalidade == 1) {
        if (indice == 0 || indice == 4 || indice == 6) {
            return 0;
        }
        return 1;
    }
    exit(0);
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
    fseek(arquivo, 0L, SEEK_SET);//adicionei esse fseek para funcionar
	fwrite("0", sizeof(char), 1, arquivo);
}

void insereInt(FILE* arquivo, int insercao, int flagTipagem) {
    int intNulo = -1;

    switch (flagTipagem) {
        case 0:
            if (insercao != 0 && insercao != -1) {
                fwrite(&insercao, sizeof(int), 1, arquivo);
            } else {
                fwrite(&intNulo, sizeof(int), 1, arquivo);
            }
            break;
        case 1:
            if (insercao != '\0' && insercao != '$') {
                fwrite(&insercao, sizeof(char), 1, arquivo);
            } else {
                preenchimentoComSifrao(arquivo, 0, tamUnidadeMedida);
            }
            break;
        default:
            break;
    }
}

void insereString(FILE* arquivo, char* insercao, int tamanhoCampo, int isFixo) {
    fwrite(insercao, sizeof(char), strlen(insercao), arquivo);
    if (isFixo) {
        preenchimentoComSifrao(arquivo, strlen(insercao), tamanhoCampo);
    } else {
        fwrite("|", sizeof(char), 1, arquivo);
    }
}

void insereRegistro (FILE* arquivo, registro aux) {
    criaInicioRegistro(arquivo);

    insereInt(arquivo, aux.idConecta, 0);
    insereString(arquivo, aux.siglaPais, tamSiglaPais, 1);
    insereInt(arquivo, aux.idPoPsConectado, 0);
    insereInt(arquivo, aux.unidadeMedida, 1);
    insereInt(arquivo, aux.velocidade, 0);
    insereString(arquivo, aux.nomePoPs, 0, 0);
    insereString(arquivo, aux.nomePais, 0, 0);

    int tamOcupadoRegistro = 22 + strlen(aux.nomePoPs) + strlen(aux.nomePais);
    preenchimentoComSifrao(arquivo, tamOcupadoRegistro, tamRegistro);
}

void criaInicioRegistro(FILE* arqSaida) {
    fwrite("0", sizeof(char), 1, arqSaida);

    int inicializar = -1;
    fwrite(&inicializar, sizeof(int), 1, arqSaida);
}
