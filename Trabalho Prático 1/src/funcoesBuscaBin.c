#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "funcoesGerais.h"
#include "funcoesBuscaBin.h"
#include "funcoesImpressaoBin.h"

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

void selectFromWhere(FILE* arqEntrada, regCabecalho aux){
    int numBuscas;
    scanf("%d", &numBuscas);

    //char *descricaoCampo[numBuscas];
    //char *valorCampoBuscado[numBuscas];
    char descricaoCampo[numBuscas][campoMaximo];
    char valorCampoBuscado[numBuscas][campoMaximo];
    int indiceCampoBuscado[numBuscas];
    for (int i = 0; i < numBuscas; i++){
        //scanf("%ms", &descricaoCampo[i]);
        scanf("%s", descricaoCampo[i]);
        indiceCampoBuscado[i] = descobreCampoBuscado(descricaoCampo[i]);
        if (temAspas(indiceCampoBuscado[i], 0)) {
            scan_quote_string(valorCampoBuscado[i]);
        }else {
            scanf("%s", valorCampoBuscado[i]);
        }
        
    }
   

    for(int i = 0; i < numBuscas; i++){
        printf("Busca %d\n", i + 1);
        int encadeamento;
        char removido;
        int numEncontrados = 0;
        for(int rrn = 0; rrn < aux.proxRRN; rrn++){
            fseek(arqEntrada, 960 + (64 * rrn), SEEK_SET);
            
            fread(&removido, sizeof(char), 1, arqEntrada);
            if(removido == '1'){
                continue;
            }

            registro aux = inicializaRegistro();
            fread(&encadeamento, sizeof(int), 1, arqEntrada);
            fread(&aux.idConecta, sizeof(int), 1, arqEntrada);
            fread(aux.siglaPais, sizeof(char), tamSiglaPais, arqEntrada);
            fread(&aux.idPoPsConectado, sizeof(int), 1, arqEntrada);
            fread(&aux.unidadeMedida, sizeof(char), tamUnidadeMedida, arqEntrada);
            fread(&aux.velocidade, sizeof(int), 1, arqEntrada);
            if (fscanf(arqEntrada, "%[^|]", aux.nomePoPs) == 0){
                aux.nomePoPs[0] = '\0';
            }
            fseek(arqEntrada, 1, SEEK_CUR);
            if (fscanf(arqEntrada, "%[^|]", aux.nomePais) == 0){
                aux.nomePoPs[0] = '\0';
            }
            
            if (campoEncontrado(indiceCampoBuscado[i], valorCampoBuscado[i], aux)) {
                numEncontrados++;
                imprimeRegistro(aux);
                printf("\n");
            }

        }
        
        if (!numEncontrados){
            printf("Registro inexistente.\n");    
            printf("\n");
        }

        printf("Numero de paginas de disco: %d\n", aux.nroPagDisco);        
        printf("\n");

        //free(descricaoCampo);
    }
}

void atualizaStatusEscrita (FILE* arquivo) {
    fseek(arquivo, 0L, SEEK_SET);//adicionei esse fseek para funcionar
	fwrite("0", sizeof(char), 1, arquivo);
}

void apagaRegistro(FILE* arquivo, int topo) {
    fwrite("1", sizeof(char), 1, arquivo);
    fwrite(&topo, sizeof(int), 1, arquivo);
    preenchimentoComSifrao(arquivo, 5, tamRegistro);
}

void remocaoLogica(FILE* arqEntrada, regCabecalho* cabecalho) {
    int numBuscas;
    scanf("%d", &numBuscas);

    fseek(arqEntrada, 0L, SEEK_END);
    int tamanhoArq = ftell(arqEntrada);
    int numRegistros = (tamanhoArq - 960) / 64;

    //char *descricaoCampo[numBuscas];
    //char *valorCampoBuscado[numBuscas];
    char descricaoCampo[numBuscas][campoMaximo];
    char valorCampoBuscado[numBuscas][campoMaximo];
    int indiceCampoBuscado[numBuscas];
    for (int i = 0; i < numBuscas; i++){
        //scanf("%ms", &descricaoCampo[i]);
        scanf("%s", descricaoCampo[i]);
        indiceCampoBuscado[i] = descobreCampoBuscado(descricaoCampo[i]);
        if (temAspas(indiceCampoBuscado[i], 0)) {
            scan_quote_string(valorCampoBuscado[i]);
        }else {
            scanf("%s", valorCampoBuscado[i]);
        }   
    }

    for(int i = 0; i < numBuscas; i++){
        int encadeamento;
        char removido;
        for(int rrn = 0; rrn < numRegistros; rrn++) {
            fseek(arqEntrada, 960 + (64 * rrn), SEEK_SET);

            fread(&removido, sizeof(char), 1, arqEntrada);
            if(removido == '1'){
                continue;
            }

            registro aux = inicializaRegistro();
            fread(&encadeamento, sizeof(int), 1, arqEntrada);
            fread(&aux.idConecta, sizeof(int), 1, arqEntrada);
            fread(aux.siglaPais, sizeof(char), tamSiglaPais, arqEntrada);
            fread(&aux.idPoPsConectado, sizeof(int), 1, arqEntrada);
            fread(&aux.unidadeMedida, sizeof(char), tamUnidadeMedida, arqEntrada);
            fread(&aux.velocidade, sizeof(int), 1, arqEntrada);
            if (fscanf(arqEntrada, "%[^|]", aux.nomePoPs) == 0){
                aux.nomePoPs[0] = '\0';
            }
            fseek(arqEntrada, 1, SEEK_CUR);
            if (fscanf(arqEntrada, "%[^|]", aux.nomePais) == 0){
                aux.nomePoPs[0] = '\0';
            }
            
            if (campoEncontrado(indiceCampoBuscado[i], valorCampoBuscado[i], aux)) {
                fseek(arqEntrada, 960 + (64 * rrn), SEEK_SET);
                apagaRegistro(arqEntrada, cabecalho->topo);
                cabecalho->topo = rrn;
                cabecalho->nroRegRem++;
            }
        }

        //free(descricaoCampo);
    }
    cabecalho->status = '1';
}

int gravaInt(char* entrada) {
    if (!strcmp(entrada, "NULO")) {
        return 0;
    } else {
        return atoi(entrada);
    }
}

void insertInto(FILE* arquivo, regCabecalho* cabecalho) {
    int numInsercoes;
    scanf("%d", &numInsercoes);


    registro aux[numInsercoes];
    char entrada[7][campoMaximo];
    for (int insercao = 0; insercao < numInsercoes; insercao++) {
        for (int indice = 0; indice < 7; indice++) {
            if(temAspas(indice, 1)) {
                scan_quote_string(entrada[indice]);
            } else {
                scanf(" %s", entrada[indice]);
            }
            switch(indice){
                case 0:
                    aux[insercao].idConecta = gravaInt(entrada[indice]);
                    break;
                case 1:
                    strcpy(aux[insercao].nomePoPs, entrada[indice]);
                    break;
                case 2:
                    strcpy(aux[insercao].nomePais, entrada[indice]);
                    break;
                case 3:
                    strcpy(aux[insercao].siglaPais, entrada[indice]);
                    break;
                case 4:
                    aux[insercao].idPoPsConectado = gravaInt(entrada[indice]);
                    break;
                case 5:
                    aux[insercao].unidadeMedida = entrada[indice][0];
                    break;
                case 6:
                    aux[insercao].velocidade = gravaInt(entrada[indice]);
                break;
            }
        }
    }

    for(int insercao = 0; insercao < numInsercoes; insercao++) {
        if(cabecalho->nroRegRem) {
            fseek(arquivo, (961 + (cabecalho->topo * 64)), SEEK_SET);
            fread(&(cabecalho->topo), sizeof(int), 1, arquivo);
            fseek(arquivo, -5, SEEK_CUR);
            insereRegistro(arquivo, aux[insercao]);
            cabecalho->nroRegRem--;
        } else {
            fseek(arquivo, (960 + (cabecalho->proxRRN * 64)), SEEK_SET);
            insereRegistro(arquivo, aux[insercao]);
            cabecalho->proxRRN++;
        }
            
    }
    cabecalho->status = '1';
}
