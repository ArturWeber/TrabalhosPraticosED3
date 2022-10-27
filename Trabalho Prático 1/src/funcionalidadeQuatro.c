#include <stdio.h>
#include <math.h>
#include "headerFuncoes.h"

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
                fwrite("1", sizeof(char), 1, arqEntrada);
                fwrite(&(cabecalho->proxRRN), sizeof(int), 1, arqEntrada);
                preenchimentoComSifrao(arqEntrada, 5, tamRegistro);
                cabecalho->proxRRN = rrn;
                cabecalho->nroRegRem++;
            }
        }

        //free(descricaoCampo);
    }
    cabecalho->status = '1';
}

void funcQuatro(char *nomeArqEntrada){
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb+");
    testaErroArquivo(arqEntrada);

    regCabecalho aux = recuperaCabecalho(arqEntrada);
    verificaStatusLeitura(aux.status);
    atualizaStatusEscrita(arqEntrada);

    remocaoLogica(arqEntrada, &aux);
    atualizaRegCabecalho(arqEntrada, aux); 

    fclose(arqEntrada);
    binarioNaTela(nomeArqEntrada);
}
