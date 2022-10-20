#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerFuncoes.h"

void criaRegCabecalho(FILE* arq) {
    fwrite("1", sizeof(char), 1, arq);
    int topo = -1;
    fwrite(&topo, sizeof(int), 1, arq);
    int zero = 0;
    for(int i = 0; i < 4; i++) {
        fwrite(&zero, sizeof(int), 1, arq);
    }
    for(int i = 0; i < 939; i++) {
        fwrite("$", sizeof(char), 1, arq);
    }
}

void TratamentoDeRegistro(FILE* arqSaida, int TamUsado){
    int tamanho;
    //verifica o numero de bytes que foram preenchidos e compara se é menor que a capacidade maxima
    if (TamUsado < linhaMaxima) {
        tamanho = TamUsado;
    } else {
        tamanho = linhaMaxima;
    }

    //coloca o \0 onde a string acabou, mesmo que tenha sido usado todos os bytes, um será armazanado para o null
    //campo[tamanho] = '\0'; //Não precisa dessa parte

    //adiciona lixo em bytes não preenchido no campo
    for (int i = (tamanho+1); i < linhaMaxima - 1; i++){
        putc('$', arqSaida);
    }
    putc('#', arqSaida);
    return;
}

void createTable(FILE* arqEntrada, FILE* arqSaida) {
    registro aux;
    int TamUsado;
    //char linha[linhaMaxima];
    //int i = 0;
    //char* token;

    //strings auxiliares
    char idcon[10] = "";
    char idpops[10] = "";
    char vel[10] = "";
    char caractere[2] = "";

    //inteiros auxiliares
    int TamNomePops = 0;
    int TamNomePais = 0;
    int TamSiglaPais = 0;
    int TamUniMed = 0;
    int TamIdPops = 0;
    int TamVel = 0;

    int contvir;//contador de virgulas

    fseek(arqEntrada, 79, SEEK_SET);
    
    while((caractere[0] = (char) fgetc(arqEntrada)) != '\0' && !(feof(arqEntrada))){
        contvir = 0;
        TamUsado = 0;
        TamNomePops = 0;
        TamNomePais = 0;
        TamSiglaPais = 0;
        TamUniMed = 0;
        TamIdPops = 0;
        TamVel = 0;
        do{//esse laço é responsavel por pegar caractere por caractere até acabar a linha
            if(caractere[0] == ','){//verifica se o caractere pego é uma virgula pra add as info em outro campo
                contvir++;
                continue;
            }
            switch (contvir)
            {
            case 0:
                strcat(idcon, caractere);
                break;
            
            case 1:
                strcat(aux.nomePoPs, caractere);
                TamNomePops++;
                break;

            case 2:
                strcat(aux.nomePais, caractere);
                TamNomePais++;
                break;
            
            case 3:
                strcat(aux.siglaPais, caractere);
                TamSiglaPais++;
                break;

            case 4:
                strcat(idpops, caractere);
                TamIdPops = 1;
                break;

            case 5:
                strcpy(aux.unidadeMedida, caractere);
                TamUniMed++;
                break;
            
            case 6:
                strcat(vel, caractere);
                TamVel = 1;
                break;

            default:
                break;
            }
            
            
        }while ((caractere[0] = (char) fgetc(arqEntrada)) != '\n' && !(feof(arqEntrada)));

        //caractere[0] = '\0';

        aux.idConecta = atoi(idcon);//transforma em inteiro o conteudo dessas strings auxiliares
        
        aux.idPoPsConectado = atoi(idpops);
        aux.velocidade = atoi(vel);

        fwrite(&aux.idConecta, sizeof(int), 1, arqSaida);//adiciona no arquivo de saida cada campo
        fprintf(arqSaida, "|");
        if(TamNomePops != 0)
            fwrite(aux.nomePoPs, sizeof(char), TamNomePops, arqSaida);
        fprintf(arqSaida, "|");
        if(TamNomePais != 0)
            fwrite(aux.nomePais, sizeof(char), TamNomePais, arqSaida);
        fprintf(arqSaida, "|");
        if(TamSiglaPais != 0)
            fwrite(aux.siglaPais, sizeof(char), TamSiglaPais, arqSaida);
        fprintf(arqSaida, "|");
        if(TamIdPops == 1 && aux.idPoPsConectado != 0)
            fwrite(&aux.idPoPsConectado, sizeof(int), TamIdPops, arqSaida);
        fprintf(arqSaida, "|");
        if(TamUniMed != 0)
            fwrite(aux.unidadeMedida, sizeof(char), TamUniMed, arqSaida);
        else{
            TamIdPops = 0;
        }
        fprintf(arqSaida, "|");
        if(TamVel == 1 && aux.velocidade != 0)
            fwrite(&aux.velocidade, sizeof(int), TamVel, arqSaida);
        else{
            TamVel = 0;
        }
        fprintf(arqSaida, "|");
        

        TamUsado = 4+TamNomePais+TamNomePops+TamSiglaPais+(TamIdPops*4)+(TamVel*4)+7;
        // printf("%d|", aux.idConecta);//imprime os campos para verificar o funcionamento
        // printf("%s|", aux.nomePoPs);
        // printf("%s|", aux.nomePais);
        // printf("%s|", aux.siglaPais);
        // printf("%d|", aux.idPoPsConectado);
        // printf("%s|", aux.unidadeMedida);
        // printf("%d|\n", aux.velocidade);

        TratamentoDeRegistro(arqSaida, TamUsado);
        
        strcpy(idcon, "");//reinicializa strings para uso de concatenação
        strcpy(idpops, "");
        strcpy(vel, "");
        strcpy(aux.nomePais, "");
        strcpy(aux.nomePoPs, "");
        strcpy(aux.siglaPais, "");
        aux.velocidade = 0;
        aux.idPoPsConectado = 0;

    }
}