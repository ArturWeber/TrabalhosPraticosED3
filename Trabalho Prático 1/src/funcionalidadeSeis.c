#include <stdio.h>
#include "headerFuncoes.h"


void compactacao(FILE* arqEntrada, FILE* arqSaida, regCabecalho* cabecalho){
    int removido;
    int encadeamento;
    for(int rrn = 0; rrn < cabecalho->proxRRN; rrn++){
        fseek(arqEntrada, 960 + (64 * rrn), SEEK_SET);

        fread(&removido, sizeof(char), 1, arqEntrada);
        fread(&encadeamento, sizeof(int), 1, arqEntrada);
        if(removido == '1'){
            cabecalho->proxRRN--;
            cabecalho->nroRegRem--;
            continue;
        }

        registro aux = inicializaRegistro();
        fread(&aux.idConecta, sizeof(int), 1, arqEntrada);
        fread(aux.siglaPais, sizeof(char), tamSiglaPais, arqEntrada);
        fread(&aux.idPoPsConectado, sizeof(int), 1, arqEntrada);
        fread(&aux.unidadeMedida, sizeof(char), tamUnidadeMedida, arqEntrada);
        fread(&aux.velocidade, sizeof(int), 1, arqEntrada);
        fscanf(arqEntrada, "%[^|]", aux.nomePoPs);
        fseek(arqEntrada, 1, SEEK_CUR);
        fscanf(arqEntrada, "%[^|]", aux.nomePais);

        insereRegistro(arqSaida, aux);
    }
    cabecalho->topo = -1;
    cabecalho->status = '1';
    cabecalho->qttCompacta++;
}

void manipulaArquivoDuplicata (char* nomeArqOriginal, char* nomeArqTemporario) {
    remove(nomeArqOriginal);
    rename(nomeArqTemporario, nomeArqOriginal);
}   

void funcSeis(char *nomeArqEntrada){
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);
    
    FILE* arqSaida;
    arqSaida = fopen("temporario.bin", "wb");
    testaErroArquivo(arqSaida);
    regCabecalho aux = inicializaCabecalho();
    atualizaRegCabecalho(arqSaida, aux);

    aux = recuperaCabecalho(arqEntrada);
    verificaStatusLeitura(aux.status);

    compactacao(arqEntrada, arqSaida, &aux);
    atualizaRegCabecalho(arqEntrada, aux); 
    fclose(arqEntrada);
    fclose(arqSaida);

    manipulaArquivoDuplicata(nomeArqEntrada, "temporario.bin");
    
    binarioNaTela(nomeArqEntrada);
}