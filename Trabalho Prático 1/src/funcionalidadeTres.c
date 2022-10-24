#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerFuncoes.h"


// void buscaNomePoPs(FILE* arquivo, registro* aux){

// }

// void buscaNomePais(FILE* arquivo, registro* aux){

// }

void buscaIdConecta(FILE* arquivo, registro* aux, int idBusca){
    char removido;

    fread(&removido, sizeof(char), 1, arquivo);
    fseek(arquivo, 4, SEEK_CUR);
    fread(&aux->idConecta, sizeof(int), 1, arquivo);

    if(aux->idConecta == idBusca){
        fread(aux->siglaPais, sizeof(char), tamSiglaPais, arquivo);
        fread(&aux->idPoPsConectado, sizeof(int), 1, arquivo);
        fread(&aux->unidadeMedida, sizeof(char), tamUnidadeMedida, arquivo);
        fread(&aux->velocidade, sizeof(int), 1, arquivo);
        fscanf(arquivo, "%[^|]", aux->nomePoPs);
        fseek(arquivo, 1, SEEK_CUR);
        fscanf(arquivo, "%[^|]", aux->nomePais);
        return;
    }else{
        aux->idConecta = -1;
        return;
    }
    
    
}

void buscaIdPoPs(FILE* arquivo, registro* aux, int idBusca){
    char removido;

    fread(&removido, sizeof(char), 1, arquivo);
    fseek(arquivo, 11, SEEK_CUR);
    fread(&aux->idPoPsConectado, sizeof(int), 1, arquivo);
    printf("%d ", aux->idConecta);
    
    if(aux->idPoPsConectado == idBusca){
        fseek(arquivo, -10, SEEK_CUR);
        fread(&aux->idConecta, sizeof(int), 1, arquivo);
        fread(aux->siglaPais, sizeof(char), tamSiglaPais, arquivo);
        fread(&aux->idPoPsConectado, sizeof(int), 1, arquivo);
        fread(&aux->unidadeMedida, sizeof(char), tamUnidadeMedida, arquivo);
        fread(&aux->velocidade, sizeof(int), 1, arquivo);
        fscanf(arquivo, "%[^|]", aux->nomePoPs);
        fseek(arquivo, 1, SEEK_CUR);
        fscanf(arquivo, "%[^|]", aux->nomePais);
        return;
    }else{
        aux->idConecta = -1;
        return;
    }
}

void selectFromWhere(FILE* arqEntrada){
    int numBusca, total, tam, numPesquisado;
    //char palavraPesquisada;
    char nomeCampo[campoMaximo];
    
    scanf("%d", &numBusca);
    total = 0;
    fseek(arqEntrada, 0, SEEK_END);
    tam = (ftell(arqEntrada)-960)/64;

    registro aux[tam];


    for(int i = 0; i < numBusca; i++){
        scanf("%s", nomeCampo);
        
        // if(!strcmp(nomeCampo, "nomePoPs"))
        //     buscaNomePops(arqEntrada, &aux[i]);
        // if(!strcmp(nomeCampo, "nomePais"))
        //     buscaNomePais(arqEntrada, &aux[i]);
        if(!strcmp(nomeCampo, "idConecta")){
            scanf("%d", &numPesquisado);
            for(int j = 0; j < tam; j++){
                fseek(arqEntrada, 960+(64*j), SEEK_SET);
                buscaIdConecta(arqEntrada, &aux[total], numPesquisado);
                if(aux[total].idConecta != -1){
                    total++;
                }
                
            }
        }

        if(!strcmp(nomeCampo, "idPoPsConectado")){
            scanf("%d", &numPesquisado);
            for(int j = 0; j < tam; j++){
                fseek(arqEntrada, 960+(64*j), SEEK_SET);
                buscaIdPoPs(arqEntrada, &aux[total], numPesquisado);
                if(aux[total].idConecta != -1){
                    total++;
                }
            }
        }
        // if(!strcmp(nomeCampo, ""))
        //     buscaNomePais(arqEntrada);
        i++;
    }

    for(int j = 0; j < total; j++){
        printf("Identificador do ponto: %d\n", aux[j].idConecta);
        if(strlen(aux[j].nomePoPs) > 1)
            printf("Nome do ponto: %s\n", aux[j].nomePoPs);
        if(strlen(aux[j].nomePais) > 1)
            printf("Pais de localizacao: %s\n", aux[j].nomePais);
        if(strcmp(aux[j].siglaPais, "$$"))
            printf("Sigla do pais: %s\n", aux[j].siglaPais);
        if(aux[j].idPoPsConectado != -1)
            printf("Identificador do ponto conectado: %d\n", aux[j].idPoPsConectado);
        if(aux[j].velocidade != -1)
            printf("Velocidade de transmissao: %d %cbps\n", aux[j].velocidade, aux[j].unidadeMedida);
        printf("\n");
    }
}
    



void funcTres(char nomeArqEntrada[]){
    FILE* arqEntrada;
    arqEntrada = fopen(nomeArqEntrada, "rb");
    testaErroArquivo(arqEntrada);

    selectFromWhere(arqEntrada);

    fclose(arqEntrada);
}

