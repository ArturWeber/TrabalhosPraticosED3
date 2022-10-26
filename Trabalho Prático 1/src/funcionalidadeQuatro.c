#include <stdio.h>
#include <math.h>
#include "headerFuncoes.h"

void remocaoLogica(FILE* arqEntrada) {
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
        if (temAspas(indiceCampoBuscado[i])) {
            scan_quote_string(valorCampoBuscado[i]);
        }else {
            scanf("%s", valorCampoBuscado[i]);
        }
        
    }
   
    for(int i = 0; i < numBuscas; i++){
        int encadeamento;
        char removido;
        int j = 0;
        while(j < numRegistros){
            fseek(arqEntrada, 960 + (64 * j), SEEK_SET);

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
                fseek(arqEntrada, -64, SEEK_CUR);
                fwrite('1', sizeof(char), 1, arqEntrada);
                preenchimentoComSifrao(arqEntrada, 2, tamRegistro);
            }
            j++;
        }

        //free(descricaoCampo);
    }
}

void funcQuatro(char *nomeArqEntrada){
    FILE* arqEntrada;
    
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);
    verificaStatus(arqEntrada);

    remocaoLogica(arqEntrada);

    fclose(arqEntrada);
}