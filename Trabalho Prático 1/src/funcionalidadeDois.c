#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "headerFuncoes.h"

void selectFrom(FILE* arqEntrada, regCabecalho cabecalho){
    int encadeamento;
    char removido;

    if (cabecalho.nroPagDisco == 1) {
        printf("Registro inexistente.\n");
        printf("\n");
    }
    
    for(int rrn = 0; rrn < cabecalho.proxRRN; rrn++){
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
        fscanf(arqEntrada, "%[^|]", aux.nomePoPs);
        fseek(arqEntrada, 1, SEEK_CUR);
        fscanf(arqEntrada, "%[^|]", aux.nomePais);

        imprimeInt(aux.idConecta, "Identificador do ponto: %d\n", 0);
        imprimeString(aux.nomePoPs, "Nome do ponto: %s\n");
        imprimeString(aux.nomePais, "Pais de localizacao: %s\n");
        imprimeString(aux.siglaPais, "Sigla do pais: %s\n");
        imprimeInt(aux.idPoPsConectado, "Identificador do ponto conectado: %d\n", 0);
        imprimeInt(aux.velocidade, "Velocidade de transmissao: %d", 0);
        imprimeInt(aux.unidadeMedida, " %cbps\n", 1);

        printf("\n");
    }

    printf("Numero de paginas de disco: %d\n", cabecalho.nroPagDisco);
    printf("\n");

}

void funcDois(char *nomeArqEntrada){
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);
    
    regCabecalho aux = recuperaCabecalho(arqEntrada);
    verificaStatusLeitura(aux.status);

    selectFrom(arqEntrada, aux);

    fclose(arqEntrada);
}
