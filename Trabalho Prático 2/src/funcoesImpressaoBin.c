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
 *         Conteudo arquivo funcoesImpressaoBin:             *
 *   Funcoes secundarias das funcionalidades                 *
 * 1 (createTable), 2 (selectFrom) e 6 (compactacao).        *
 * Organizadas juntas pois envolvem funcoes em comum, princi *
 * palmente entre a funcionalidade 1 e 6.                    *
*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesGerais.h"

//Funcao utilizada pelo procedimento insereRegistro, e insere o campo no .bin quando seu valor
//e de char ou int. A flagTipagem indica se o tipo da insercao e 0, int, ou 1, char
void insereInt(FILE* arquivo, int insercao, int flagTipagem) {
    //Inicializa o valor para quando int e nulo
    int intNulo = -1;

    switch (flagTipagem) {
        case 0:
            //Escreve inteiro caso seja diferente de 0 (lido de string) e -1 (lido de .bin)
            if (insercao != 0 && insercao != -1) {
                fwrite(&insercao, sizeof(int), 1, arquivo);
            } else {
                fwrite(&intNulo, sizeof(int), 1, arquivo);
            }
            break;
        case 1:
            //Escreve char caso seja diferente de \0 (lido de string) e $ (lido de .bin)
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

//Funcao utilizada pelo procedimento insereRegistro, e insere o campo no .bin quando seu valor
//e de string. tamanhoCampo indica o tamanho do campo fixo e isFixo indica se o campo e fixo
void insereString(FILE* arquivo, char* insercao, int tamanhoCampo, int isFixo) {
    //Insere a string no arquivo
    fwrite(insercao, sizeof(char), strlen(insercao), arquivo);
    //Se for fixo utiliza o preenchimento, senao escreve o delimitador de campo
    if (isFixo) {
        preenchimentoComSifrao(arquivo, strlen(insercao), tamanhoCampo);
    } else {
        fwrite("|", sizeof(char), 1, arquivo);
    }
}

//Funcao utilizada pelo procedimento insereRegistro e cria o cabecalho do registro, contendo
//os parametros removido e encadeamento 
void criaInicioRegistro(FILE* arqSaida) {
    fwrite("0", sizeof(char), 1, arqSaida);

    int inicializar = -1;
    fwrite(&inicializar, sizeof(int), 1, arqSaida);
}

//Funcionalidade que insere o registro no arquivo .bin, depois preenchendo-o com sifroes
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

//Funcao do tipo regCabecalho que inicializa o cabecalho com valores iniciais especificados no documento 
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

//Funcao que cria uma "transformada" da string que a funcionalidade 1 recebe em cada linha do csv e
//efetua tratamento da string para que a funcao strtok consiga separa-la corretamente. Essencialmente 
//adiciona espacos entre virgulas consecutivas.
void transfString(char linhaInicial[], char linhaFinal[]) {
    int posicao = 0;
    for(unsigned long i = 0; i < (strlen(linhaInicial) - 1); i++) {
        linhaFinal[posicao] = linhaInicial[i];
        //caso hajam duas virgulas em seguida ou uma unica no final da linha, adiciona espaco
        if ((linhaInicial[i] == ',') && (linhaInicial[i + 1] == ',' || (i == strlen(linhaInicial) - 2))) {
            linhaFinal[posicao + 1] = ' ';
            posicao++; 
        }
        posicao++;
    }
    //Finaliza string com \0 
    linhaFinal[posicao] = '\0';
}

//Funcionalidade que cria uma "transformada inversa" das strings depois que foram separadas pelo strktok.
//Essencialmente lida removendo espacos vazios no campo. 
void transfInversaString(char *string) {  
    int comprimento = strlen(string);
    int ultimoDigito = -1 ;
    //Verifica qual o ultimo digito da string
    for (int i = 0; i < comprimento; i++) {
        if (string[i] != ' ') {
            ultimoDigito = i;
        }
    }
    //Caso nao ache ultimo digito, reduz a string a "nada" e caso contrario coloca o final da string apos o ultimo digito
    if (ultimoDigito == -1) {
        string[0] = '\0';
    } else {
        string[ultimoDigito + 1] = '\0';
    }
}

//Funcao secundaria da funcionalidade 1, insere os arquivos do csv no binario
void createTable(FILE* arqEntrada, FILE* arqSaida, regCabecalho* cabecalho) {

    //Cria registro auxiliar para inserir e variaveis para armazenar cada linha do csv 
    registro aux = inicializaRegistro();
    char linhaDestratada[linhaMaxima];
    char linhaTratada[linhaMaxima];
    //Le cabecalho do csv
    fgets(linhaDestratada, linhaMaxima, arqEntrada);
    
    char* token;
    int i = 0;
    //Le linha a linha do csv
    while (fgets(linhaDestratada, linhaMaxima, arqEntrada) != NULL) {
        //Transforma linha para strtok conseguir ler
        transfString(linhaDestratada, linhaTratada);
        token = strtok(linhaTratada, ",");
        //Le Coluna a Coluna e adiciona no registro auxiliar 
        while(token != NULL) {
            i++;
            switch(i){
                case 1:
                    aux.idConecta = atoi(token);
                    break;
                case 2:
                    strcpy(aux.nomePoPs, token);
                    transfInversaString(aux.nomePoPs);
                    break;
                case 3:
                    strcpy(aux.nomePais, token);
                    transfInversaString(aux.nomePais);
                    break;
                case 4:
                    strcpy(aux.siglaPais, token);
                    transfInversaString(aux.siglaPais);
                    break;
                case 5:
                    aux.idPoPsConectado = atoi(token);
                    break;
                case 6:
                    aux.unidadeMedida = token[0];
                    transfInversaString(&aux.unidadeMedida);
                    break;
                case 7:
                    aux.velocidade = atoi(token);
                    i = 0;
                break;
            }
            token = strtok(NULL, ",");
        }
        //Incrementa o proxRRN do cabecalho recebido de parametro
        cabecalho->proxRRN++;

        //Insere o registro auxiliar no arquivo .bin
        insereRegistro(arqSaida, aux);
        
    }
    //Atualiza o cabecalho para '1', indicando sucesso do procedimento
    cabecalho->status = '1';
}

//Imprime variaveis int ou char lidas do .bin , flagTipagem indica 0 para int e 1 para char
void imprimeInt(int impressao, char *apresentacao, int flagTipagem) {
    switch (flagTipagem) {
    case 0:
        //Imprime se valor nao e nulo
        if (impressao != -1) {
            printf(apresentacao, impressao);
        }
        break;
    case 1:
        //Imprime se valor nao e nulo
        if (impressao != '$') {
            printf(apresentacao, impressao);
        }
        break;
    default:
        break;
    }
    
}

//Imprime string retirada do .bin
void imprimeString(char *impressao, char *apresentacao) {
    if (impressao[0] != '$' && impressao[0] != '\0' && strlen(impressao) > 1) {
        printf(apresentacao, impressao);
    }
}

//Imprime registro
void imprimeRegistro(registro aux) {
    imprimeInt(aux.idConecta, "Identificador do ponto: %d\n", 0);
    imprimeString(aux.nomePoPs, "Nome do ponto: %s\n");
    imprimeString(aux.nomePais, "Pais de localizacao: %s\n");
    imprimeString(aux.siglaPais, "Sigla do pais: %s\n");
    imprimeInt(aux.idPoPsConectado, "Identificador do ponto conectado: %d\n", 0);
    imprimeInt(aux.velocidade, "Velocidade de transmissao: %d", 0);
    imprimeInt(aux.unidadeMedida, " %cbps\n", 1);
}

//Funcao secundaria da funcionalidade 2, le .bin e o imprime
void selectFrom(FILE* arqEntrada, regCabecalho cabecalho){
    int encadeamento;
    char removido;

    //Se o numero de paginas de disco for 1 (somente cabecalho), nao ha registro
    if (cabecalho.nroPagDisco == 1) {
        printf("Registro inexistente.\n");
        printf("\n");
    }
    
    //Le todo o lixo do cabecalho para mover ponteiro e em seguida le registro a registro e imprime
    leLixo(arqEntrada, 939);
    for(int rrn = 0; rrn < cabecalho.proxRRN; rrn++){
        fread(&removido, sizeof(char), 1, arqEntrada);
        //Se for removido nao imprime
        if(removido == '1'){
            leLixo(arqEntrada, 63);
            continue;
        }
        //Senao, le registro e armazena no auxiliar
        registro aux = inicializaRegistro();
        fread(&encadeamento, sizeof(int), 1, arqEntrada);
        //le todos os campos de um registro
        leRegistro(arqEntrada, &aux);

        //Imprime auxiliar lido
        imprimeRegistro(aux);
        //Le lixo do registro para mover ponteiro
        int comprimentoLixo = 42 - strlen(aux.nomePoPs) - strlen(aux.nomePais);
        leLixo(arqEntrada, comprimentoLixo);

        printf("\n");
    }
    //Imprime numero de paginas de disco
    printf("Numero de paginas de disco: %d\n", cabecalho.nroPagDisco);
    printf("\n");

}

//Funcao secundaria da funcionalidade 6, compacta arquivo 
void compactacao(FILE* arqEntrada, FILE* arqSaida, regCabecalho* cabecalho){
    int removido;
    int encadeamento;
    int numRegistros = cabecalho->proxRRN;

    leLixo(arqEntrada, 939);
    //Le registro a registro do arqEntrada
    for(int rrn = 1; rrn <= numRegistros; rrn++){
        
        fread(&removido, sizeof(char), 1, arqEntrada);
        
        //Se foi removido, nao grava no arqSaida, diminuindo o numero de removidos e o proximo RRN
        if(removido == '1'){
            cabecalho->proxRRN--;
            cabecalho->nroRegRem--;
            leLixo(arqEntrada, 63);
            continue;
        }

        //Le registro se nao for removido
        registro aux = inicializaRegistro();
        fread(&encadeamento, sizeof(int), 1, arqEntrada);
        //le todos os campos de um registro
        leRegistro(arqEntrada, &aux);

        //Insere registro no arquivo de saida
        insereRegistro(arqSaida, aux);
        int comprimentoLixo = 42 - strlen(aux.nomePoPs) - strlen(aux.nomePais);
        leLixo(arqEntrada, comprimentoLixo);
    }
    //Atualiza o cabecalho caso o procedimento seja efetuado corretamente
    cabecalho->topo = -1;
    cabecalho->status = '1';
    cabecalho->qttCompacta++;
}
