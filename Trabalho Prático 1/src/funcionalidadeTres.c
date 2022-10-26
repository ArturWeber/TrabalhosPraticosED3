#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "headerFuncoes.h"

void selectFromWhere(FILE* arqEntrada){
    int numBuscas;
    scanf("%d", &numBuscas);

    fseek(arqEntrada, 0L, SEEK_END);
    int tamanhoArq = ftell(arqEntrada);
    int numRegistros = (tamanhoArq - 960) / 64;
    int pagDisco = (int) ceil((tamanhoArq) / (64.0 * 15.0));


    //char *descricaoCampo[numBuscas];
    //char *valorCampoBuscado[numBuscas];
    char descricaoCampo[numBuscas][campoMaximo];
    char valorCampoBuscado[numBuscas][campoMaximo];
    int indiceCampoBuscado[numBuscas];
    for (int i = 0; i < numBuscas; i++){
        //scanf("%ms", &descricaoCampo[i]);
        scanf("%s", descricaoCampo[i]);
        indiceCampoBuscado[i] = descobreCampoBuscado(descricaoCampo[i]);
        if (temAspas(indiceCampoBuscado[i])) {
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
        for(int rrn = 0; rrn < numRegistros; rrn++){
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
                imprimeInt(aux.idConecta, "Identificador do ponto: %d\n", 0);
                imprimeString(aux.nomePoPs, "Nome do ponto: %s\n");
                imprimeString(aux.nomePais, "Pais de localizacao: %s\n");
                imprimeString(aux.siglaPais, "Sigla do pais: %s\n");
                imprimeInt(aux.idPoPsConectado, "Identificador do ponto conectado: %d\n", 0);
                imprimeInt(aux.velocidade, "Velocidade de transmissao: %d", 0);
                imprimeInt(aux.unidadeMedida, " %cbps\n", 1);
                printf("\n");
            }

        }
        
        if (!numEncontrados){
            printf("Registro inexistente.\n");    
            printf("\n");
        }

        printf("Numero de paginas de disco: %d\n", pagDisco);        
        printf("\n");

        //free(descricaoCampo);
    }
}

void funcTres(char *nomeArqEntrada){
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);

    regCabecalho aux = recuperaCabecalho(arqEntrada);
    verificaStatus(aux.status);

    selectFromWhere(arqEntrada);

    fclose(arqEntrada);
}
