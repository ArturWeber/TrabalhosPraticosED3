#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

void trataCampo(char *campo, int capacidade) {
    int tamanho = strlen(campo);

    for (int i = tamanho; i < capacidade; i++){
        campo[i] = '$';
    }

    campo[capacidade - 1] = '\0'; 
}

void funcionalidade1(FILE* nomeArquivo) {
    int numReg;
    scanf("%d", &numReg);

    //cria e grava campos em um registro temporario, depois gravando os registro obtidos um a um 
    //uma abordagem de armazenamento de todos os registros em memoria e depois em armazenamento poderia ter sido tomada com a vantagem de maior velocidade, porem mais uso de RAM
    pessoa temporario;
    for(int i = 0; i < numReg; i++){
        scanf("%s", temporario.primeiroNome);
        trataCampo(temporario.primeiroNome, 51);
        scanf("%s", temporario.sobreNome);
        trataCampo(temporario.sobreNome, 51);
        scanf("%s", temporario.eMail);
        trataCampo(temporario.eMail, 81);
        scanf("%s", temporario.nacionalidade);
        trataCampo(temporario.nacionalidade, 51);
        scanf("%d", &temporario.idade);

        /* teste printagem
        printf("Firstname:%s\n", temporario.primeiroNome);
        printf("Lastname:%s\n", temporario.sobreNome);
        printf("Email:%s\n", temporario.eMail);
        printf("Nationality:%s\n", temporario.nacionalidade);
        printf("Age:%d\n", temporario.idade);
        */

       fwrite(temporario.primeiroNome, sizeof(char), (strlen(temporario.primeiroNome) + 1), nomeArquivo);
       fwrite(temporario.sobreNome, sizeof(char), (strlen(temporario.sobreNome) + 1), nomeArquivo);
       fwrite(temporario.eMail, sizeof(char), (strlen(temporario.eMail) + 1), nomeArquivo);
       fwrite(temporario.nacionalidade, sizeof(char), (strlen(temporario.nacionalidade) + 1), nomeArquivo);

       char idade[4];
       memset(idade, '\0', 4);
       sprintf(idade,"%d", temporario.idade);
       fwrite(idade, sizeof(char), (strlen(idade) + 1), nomeArquivo);
       // ja que estou transformando a idade em string aqui... por que nao fazer ele ser string desde o começo??
       // outra coisa!! -> sera que estou gravando da maneira correta o numero no arquivo? int eh meio diferente, seila

    }
}

void funcionalidade2() {

}

void funcionalidade3() {
    int rrn;
    scanf("%d", &rrn);

}

