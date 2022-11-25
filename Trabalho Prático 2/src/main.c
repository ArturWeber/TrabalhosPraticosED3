/************************************************************
 *            Trabalho Prático 2 - SCC0607                   *
 *                                                           *
 *      Nome: Artur Brenner Weber                            *
 *      nUSP: 12675451    Participacao: 100%                 *
 *      Nome: Aruan  Bretas de Oliveira Filho                *
 *      nUSP: 12609731    Participacao: 100%                 *
 *      Data de última atualizacao: 22/11/2022               *
 *      Ambiente de Desenvolv: VSCode 1.73.1                 *
 *      e-mail: arturweber@usp.br / aruanbretas@usp.br       *
 *                                                           *
 *                Conteudo arquivo main:                     *
 *   Funcoes principais de cada uma das funcionalidades,     *
 * alem da funcao main.                                      *
*************************************************************/

//Includes das bibliotecas padrao e dos headers de cada arquivo .c 
//por conterem as funcoes secundarias das funcionalidades 
#include <stdio.h>
#include <stdlib.h>
#include "funcoesGeraisT1.h"
#include "funcoesGeraisT2.h"
#include "funcoesBuscaBin.h"
#include "funcoesImpressaoBin.h"
#include "funcaoSete.h"
#include "funcaoOito.h"

//Funcao principal da funcionalidade 1, efetua as manipulacoes 
//principais de arquivos 
void funcUm(char *nomeArqEntrada, char *nomeArqSaida) {
    //Abre arquivos e testa
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);
    
    FILE* arqSaida;
    arqSaida = fopen(nomeArqSaida, "wb");
    testaErroArquivo(arqSaida);

    //Inicializa um registro auxiliar do tipo regCabecalho com
    //os valores iniciais de cabecalho e os insere no arquivoFinal
    regCabecalho aux = inicializaCabecalho();
    atualizaRegCabecalho (arqSaida, aux);

    //Insere dados do csv no arquivo de saida e atualiza o cabecalho
    //auxiliar conforme. Depois atualiza o cabecalho do arquivo.  
    createTable(arqEntrada, arqSaida, &aux);
    atualizaRegCabecalho (arqSaida, aux); 

    //Fecha os arquivos
    fclose(arqEntrada);
    fclose(arqSaida);

    binarioNaTela(nomeArqSaida);
}

//Funcao principal da funcionalidade 2, efetua as manipulacoes 
//principais de arquivos 
void funcDois(char *nomeArqEntrada) {
    //Abre arquivo de entrada e testa
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);
    
    //Inicializa um registro auxiliar do tipo regCabecalho com
    //os valores de cabecalho do arquivo de entrada, verificando seu status
    regCabecalho aux = recuperaCabecalho(arqEntrada);
    verificaStatusLeitura(aux.status);

    //Percorre o arquivo, imprimindo-o
    selectFrom(arqEntrada, aux);

    //Fecha o arquivo
    fclose(arqEntrada);
}

//Funcao principal da funcionalidade 3, efetua as manipulacoes 
//principais de arquivos 
void funcTres(char *nomeArqEntrada) {
    //Abre arquivo de entrada e testa
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);

    //Inicializa um registro auxiliar do tipo regCabecalho com
    //os valores de cabecalho do arquivo de entrada, verificando seu status
    regCabecalho aux = recuperaCabecalho(arqEntrada);
    verificaStatusLeitura(aux.status);

    //Percorre o arquivo buscando e imprime
    selectFromWhere(arqEntrada, aux);

    //Fecha o arquivo
    fclose(arqEntrada);
}

//Funcao principal da funcionalidade 4, efetua as manipulacoes 
//principais de arquivos 
void funcQuatro(char *nomeArqEntrada){
    //Abre arquivo de entrada e testa
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb+");
    testaErroArquivo(arqEntrada);

    //Inicializa um registro auxiliar do tipo regCabecalho com
    //os valores de cabecalho do arquivo de entrada, verificando seu status e atualizando
    regCabecalho aux = recuperaCabecalho(arqEntrada);
    verificaStatusLeitura(aux.status);
    atualizaStatusEscrita(arqEntrada);

    //Remove os arquivos pedidos e atualiza o cabecalho
    //auxiliar conforme. Depois escreve o cabecalho.
    remocaoLogica(arqEntrada, &aux);
    atualizaRegCabecalho(arqEntrada, aux); 
    
    //Fecha o arquivo
    fclose(arqEntrada);
    
    binarioNaTela(nomeArqEntrada);
}

//Funcao principal da funcionalidade 5, efetua as manipulacoes 
//principais de arquivos 
void funcCinco(char *nomeArqEntrada) {
    //Abre arquivo e testa
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb+");
    testaErroArquivo(arqEntrada);

    //Inicializa um registro auxiliar do tipo regCabecalho com
    //os valores de cabecalho do arquivo de entrada, verificando seu status e atualizando
    regCabecalho aux = recuperaCabecalho(arqEntrada);
    verificaStatusLeitura(aux.status);
    atualizaStatusEscrita(arqEntrada);

    //Insere os arquivos pedidos e atualiza o cabecalho
    //auxiliar conforme. Depois escreve o cabecalho. 
    insertInto(arqEntrada, &aux);
    atualizaRegCabecalho(arqEntrada, aux);
    fclose(arqEntrada);

    binarioNaTela(nomeArqEntrada);
}

//Funcao principal da funcionalidade 6, efetua as manipulacoes 
//principais de arquivos 
void funcSeis(char *nomeArqEntrada){
    //Abre o arquivo de entrada e testa
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);
    
    //Cria um arquivo temporario que se tornara o definitivo, testando 
    FILE* arqSaida;
    arqSaida = fopen("temporario.bin", "wb");
    testaErroArquivo(arqSaida);
    //Como na funcionalidade 1, inicializa os valores iniciais do cabecalho e o escreve
    regCabecalho aux = inicializaCabecalho();
    atualizaRegCabecalho(arqSaida, aux);

    //Recupera o cabecalho do arquivo original e verifica o seu status para iniciar o processo
    aux = recuperaCabecalho(arqEntrada);
    verificaStatusLeitura(aux.status);

    //Compacta o arquivo e atualiza seu cabecalho conforme
    compactacao(arqEntrada, arqSaida, &aux);
    atualizaRegCabecalho(arqSaida, aux); 

    //Fecha ambos os arquivos 
    fclose(arqEntrada);
    fclose(arqSaida);

    //Remove arquivo original e renomeia arquivo temporario para definitivo
    manipulaArquivoDuplicata(nomeArqEntrada, "temporario.bin");
    
    binarioNaTela(nomeArqEntrada);
}

void funcSete(char *nomeArqEntrada, char *nomeArqSaida) {
    //Abre arquivos e testa
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);
    
    FILE* arqSaida;
    arqSaida = fopen(nomeArqSaida, "wb+");
    testaErroArquivo(arqSaida);

    //Testa status para comecar leitura
    regCabecalho aux = recuperaCabecalho(arqEntrada);
    verificaStatusLeitura(aux.status);

    regCabecalhoIndice auxIndice = inicializaCabecalhoIndice();
    atualizaRegCabecalhoIndice(arqSaida, auxIndice);
   
    createIndex(arqEntrada, arqSaida, aux, &auxIndice);

    atualizaRegCabecalhoIndice (arqSaida, auxIndice); 

    //Fecha os arquivos
    fclose(arqEntrada);
    fclose(arqSaida);

    binarioNaTela(nomeArqSaida);
}

void funcOito(char* nomeArqEntrada, char* nomeArqIndice) {
    //Abre arquivo de entrada e testa
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);

    //Inicializa um registro auxiliar do tipo regCabecalho com
    //os valores de cabecalho do arquivo de entrada, verificando seu status
    regCabecalho aux = recuperaCabecalho(arqEntrada);
    verificaStatusLeitura(aux.status);

    //Abre arquivo de indice e testa
    FILE* arqIndice;
    arqIndice = fopen(nomeArqIndice, "rb");
    testaErroArquivo(arqIndice);

    //Inicializa um registro auxiliar do tipo regCabecalhoIndice com
    //os valores de cabecalho do arquivo de entrada, verificando seu status
    regCabecalhoIndice auxIndice = recuperaCabecalhoIndice(arqIndice);
    verificaStatusLeitura(auxIndice.status);

    //Percorre o arquivo buscando e imprime
    selectFromWhereIndice(arqEntrada, arqIndice, aux, auxIndice);

    //Fecha o arquivo
    fclose(arqEntrada);
}

//Funcao main, le as entradas e aplica um switch com as funcionalidades
int main(void) {
    int funcionalidade; 
    //char *nomeArqEntrada;
    //char *nomeArqSaida;
    //scanf("%d %ms", &funcionalidade, &nomeArqEntrada);
    char nomeArqEntrada[campoMaximo];
    char nomeArqSaida[campoMaximo];
    scanf("%d %s", &funcionalidade, nomeArqEntrada);

    switch(funcionalidade) {
        case 1:
            //scanf("%ms", &nomeArqSaida);
            scanf("%s", nomeArqSaida);
            funcUm(nomeArqEntrada, nomeArqSaida);
            //free(nomeArqSaida);
            break;
        case 2:
            funcDois(nomeArqEntrada);
            break;
        case 3:
            funcTres(nomeArqEntrada);
            break;
        case 4:
            funcQuatro(nomeArqEntrada);
            break;
        case 5:
            funcCinco(nomeArqEntrada);
            break;
        case 6:
            funcSeis(nomeArqEntrada);
            break; 
        case 7:
            scanf("%s", nomeArqSaida);
            funcSete(nomeArqEntrada, nomeArqSaida);
            break;
        case 8:
            scanf("%s", nomeArqSaida);
            funcOito(nomeArqEntrada, nomeArqSaida);
            break;
        case 9:
            printf("nao implementada!!");
            break;
        case 10:
            printf("nao implementada!!");
            break;
        default:
            printf("Comando Não Encontrado \n");
    }

    //free(nomeArqEntrada);
    return 0;

}
