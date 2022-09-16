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

    //cria e grava campos em um registro temporario, depois gravando os registro obtidos um a um 
    //uma abordagem de armazenamento de todos os registros em memoria e depois em armazenamento poderia ter sido tomada com a vantagem de maior velocidade, porem mais uso de RAM
    pessoa temporario;
    for(int i = 0; i < numReg; i++){
        scanf("%s", temporario.primeiroNome);
        trataCampo(temporario.primeiroNome, NOME_TAMANHO);
        scanf("%s", temporario.sobreNome);
        trataCampo(temporario.sobreNome, SOBRENOME_TAMANHO);
        scanf("%s", temporario.eMail);
        trataCampo(temporario.eMail, EMAIL_TAMANHO);
        scanf("%s", temporario.nacionalidade);
        trataCampo(temporario.nacionalidade, NACIONALIDADE_TAMANHO);
        scanf("%d", &temporario.idade);

       fwrite(temporario.primeiroNome, sizeof(char), NOME_TAMANHO, nomeArquivo);
       fwrite(temporario.sobreNome, sizeof(char), SOBRENOME_TAMANHO, nomeArquivo);
       fwrite(temporario.eMail, sizeof(char), EMAIL_TAMANHO, nomeArquivo);
       fwrite(temporario.nacionalidade, sizeof(char), NACIONALIDADE_TAMANHO, nomeArquivo);
       fwrite(&temporario.idade, sizeof(int), 1, nomeArquivo);
    }
}

void funcionalidade2() {

}

void funcionalidade3() {
    int rrn;
    scanf("%d", &rrn);

}

