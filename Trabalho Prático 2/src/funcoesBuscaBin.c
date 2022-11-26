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
 *   Funcoes secundarias das funcionalidades                 *
 * 3 (selectFromWhere), 4 (remocaoLogica) e 5 (insertInto).  *
 * Organizadas juntas pois envolvem funcoes em comum.        *
*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "funcoesGeraisT1.h"
#include "funcoesBuscaBin.h"
#include "funcoesImpressaoBin.h"

//Funcao fornecida para ler comandos com aspas 
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

//Funcao que verifica se o indice enviado e de campo possivelmente com ou sem aspas
//a flagFuncionalidade serve para indicar qual funcionalidade esta utilizando a funcao
//vale 0 para funcionalidades 3 e 4 e vale 1 para a funcionalidade 5
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

//Descobre qual campo esta sendo buscado pelos comandos das funcionalidades e retorna um valor definido
//para cada campo
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

//Retorna 1 caso o campoBuscado seja encontrado 
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

void leCamposDeBusca(char (*descricaoCampo)[campoMaximo], char (*valorCampoBuscado)[campoMaximo], int indiceCampoBuscado[], int numBuscas){
    for (int i = 0; i < numBuscas; i++){
        scanf("%s", descricaoCampo[i]);
        indiceCampoBuscado[i] = descobreCampoBuscado(descricaoCampo[i]);
        //Se tiver aspas, usa a funcao de ler aspas, senao, usa scanf
        if (temAspas(indiceCampoBuscado[i], 0)) {
            scan_quote_string(valorCampoBuscado[i]);
        }else {
            scanf("%s", valorCampoBuscado[i]);
        }   
    }
}

//Funcao secundaria da funcionalidade 3, busca o registro pedido e o imprime
void selectFromWhere(FILE* arqEntrada, regCabecalho aux){
    //Coleta o numero de buscas 
    int numBuscas;
    scanf("%d", &numBuscas);

    //Armazena as especificacoes de cada busca, isto e, o campo, seu valor e o indice do campo
    char descricaoCampo[numBuscas][campoMaximo];
    char valorCampoBuscado[numBuscas][campoMaximo];
    int indiceCampoBuscado[numBuscas];
    leCamposDeBusca(descricaoCampo, valorCampoBuscado, indiceCampoBuscado, numBuscas);
   
    //Efetua cada busca
    for(int i = 0; i < numBuscas; i++){
        fseek(arqEntrada, 960, SEEK_SET);
        printf("Busca %d\n", i + 1);
        int encadeamento;
        char removido;
        int numEncontrados = 0;
        //Le registro a registro procurando o que busca
        for(int rrn = 0; rrn < aux.proxRRN; rrn++){
            
            fread(&removido, sizeof(char), 1, arqEntrada);
            //Se for removido para de ler 
            if(removido == '1'){
                leLixo(arqEntrada, 63);
                continue;
            }

            //Armazena registro na variavel auxiliar
            registro aux = inicializaRegistro();
            fread(&encadeamento, sizeof(int), 1, arqEntrada);
            //le todos os campos de um registro
            leRegistro(arqEntrada, &aux);

            
            //Se encontrou o campo, imprime-o
            if (campoEncontrado(indiceCampoBuscado[i], valorCampoBuscado[i], aux)) {
                numEncontrados++;
                imprimeRegistro(aux);
                printf("\n");
            }

            int comprimentoLixo = 42 - strlen(aux.nomePoPs) - strlen(aux.nomePais);
            leLixo(arqEntrada, comprimentoLixo);

        }
        
        //Caso nao encontrou nenhum campo, imprime mensagem
        if (!numEncontrados){
            printf("Registro inexistente.\n");    
            printf("\n");
        }

        printf("Numero de paginas de disco: %d\n", aux.nroPagDisco);        
        printf("\n");

    }
}

//Atualiza status p escrita
void atualizaStatusEscrita (FILE* arquivo) {
    fseek(arquivo, 0L, SEEK_SET);
	fwrite("0", sizeof(char), 1, arquivo);
}

//Apaga registro, usado na funcionalidade 4 e modularizado caso outras funcoes precisem
//remover registros no futuro
void apagaRegistro(FILE* arquivo, int topo) {
    fwrite("1", sizeof(char), 1, arquivo);
    fwrite(&topo, sizeof(int), 1, arquivo);
    preenchimentoComSifrao(arquivo, 5, tamRegistro);
}

//Funcao secundaria da funcionalidade 4, busca e remove registros
void remocaoLogica(FILE* arqEntrada, regCabecalho* cabecalho) {
    //Le numero de buscas
    int numBuscas;
    scanf("%d", &numBuscas);

    //Le os detalhes da busca, igual funcionalidade 3
    char descricaoCampo[numBuscas][campoMaximo];
    char valorCampoBuscado[numBuscas][campoMaximo];
    int indiceCampoBuscado[numBuscas];
    leCamposDeBusca(descricaoCampo, valorCampoBuscado, indiceCampoBuscado, numBuscas);

    //Efetua cada busca
    int numRegistros = cabecalho->proxRRN;
    for(int i = 0; i < numBuscas; i++){
        int encadeamento;
        char removido;
        fseek(arqEntrada, 960, SEEK_SET);
        //Le cada registro procurando o que se busca
        for(int rrn = 0; rrn < numRegistros; rrn++) {

            fread(&removido, sizeof(char), 1, arqEntrada);
            //Se removido, ignorar
            if(removido == '1'){
                leLixo(arqEntrada, 63);
                continue;
            }


            //Le registro
            registro aux = inicializaRegistro();
            fread(&encadeamento, sizeof(int), 1, arqEntrada);
            //le todos os campos de um registro
            leRegistro(arqEntrada, &aux);
            
            //Verifica se foi encontrado e se sim, remove e atualiza os valores do cabecalho
            if (campoEncontrado(indiceCampoBuscado[i], valorCampoBuscado[i], aux)) {
                fseek(arqEntrada, 960 + (64 * rrn), SEEK_SET);
                apagaRegistro(arqEntrada, cabecalho->topo);
                cabecalho->topo = rrn;
                cabecalho->nroRegRem++;
            }else{
                int comprimentoLixo = 42 - strlen(aux.nomePoPs) - strlen(aux.nomePais);
                leLixo(arqEntrada, comprimentoLixo);
            }
        }

        //free(descricaoCampo);
    }
    //Atualiza cabecalho para 1 caso o procedimento tenha dado certo
    cabecalho->status = '1';
}

//Retorna inteiro caso nao seja nulo
int gravaInt(char* entrada) {
    if (!strcmp(entrada, "NULO")) {
        return 0;
    } else {
        return atoi(entrada);
    }
}

//Funcao secundaria da funcionalidade 5
void insertInto(FILE* arquivo, regCabecalho* cabecalho) {
    //Le o numero de insercoes
    int numInsercoes;
    scanf("%d", &numInsercoes);


    registro aux[numInsercoes];
    char entrada[7][campoMaximo];
    for (int insercao = 0; insercao < numInsercoes; insercao++) {
        //Le cada um dos campos que se quer adicionar 
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

    //Insere cada um dos campos
    for(int insercao = 0; insercao < numInsercoes; insercao++) {
        //Se houver espaco livre no meio do .bin, insere no meio e caso contrario insere no fim
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
    //Atualiza status cabecalho caso procedimento de certo
    cabecalho->status = '1';
}
