#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

void trataCampo(char *campo, int capacidade) {
    int tamanho = strlen(campo);

    campo[tamanho] = '\0'; 

    for (int i = (tamanho + 1); i < capacidade; i++){
        campo[i] = '$';
    }
}

void funcionalidade1(FILE* nomeArquivo) {
    int numReg;
    scanf("%d", &numReg);

    //cria e grava campos em um registro aux, depois gravando os registro obtidos um a um 
    //uma abordagem de armazenamento de todos os registros em memoria e depois em armazenamento poderia ter sido tomada com a vantagem de maior velocidade, porem mais uso de RAM
    pessoa aux;
    for(int i = 0; i < numReg; i++){
        scanf("%s", aux.primeiroNome);
        trataCampo(aux.primeiroNome, NOME_TAMANHO);
        scanf("%s", aux.sobreNome);
        trataCampo(aux.sobreNome, SOBRENOME_TAMANHO);
        scanf("%s", aux.eMail);
        trataCampo(aux.eMail, EMAIL_TAMANHO);
        scanf("%s", aux.nacionalidade);
        trataCampo(aux.nacionalidade, NACIONALIDADE_TAMANHO);
        scanf("%d", &aux.idade);

       fwrite(aux.primeiroNome, sizeof(char), NOME_TAMANHO, nomeArquivo);
       fwrite(aux.sobreNome, sizeof(char), SOBRENOME_TAMANHO, nomeArquivo);
       fwrite(aux.eMail, sizeof(char), EMAIL_TAMANHO, nomeArquivo);
       fwrite(aux.nacionalidade, sizeof(char), NACIONALIDADE_TAMANHO, nomeArquivo);
       fwrite(&aux.idade, sizeof(int), 1, nomeArquivo);
    }
}


void funcionalidade2(FILE* nomeArquivo) {
    pessoa aux;
    while(fread(aux.primeiroNome, sizeof(char), NOME_TAMANHO, nomeArquivo) != 0){
       fread(aux.sobreNome, sizeof(char), SOBRENOME_TAMANHO, nomeArquivo);
       fread(aux.eMail, sizeof(char), EMAIL_TAMANHO, nomeArquivo);
       fread(aux.nacionalidade, sizeof(char), NACIONALIDADE_TAMANHO, nomeArquivo);
       fread(&aux.idade, sizeof(int), 1, nomeArquivo);

       printf("Firstname: %s\n", aux.primeiroNome);
       printf("Lastname: %s\n", aux.sobreNome);
       printf("Email: %s\n", aux.eMail);
       printf("Nationality: %s\n", aux.nacionalidade);
       printf("Age: %d\n\n", aux.idade);
    }
}


void funcionalidade3() {
    int rrn;
    scanf("%d", &rrn);

}

