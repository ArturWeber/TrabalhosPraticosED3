#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

void trataCampo(char *campo, int capacidade) {
    int tamanho = strlen(campo);

    for (int i = tamanho; i < capacidade; i++){
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
        trataCampo(temporario.primeiroNome, 50);
        scanf("%s", temporario.sobreNome);
        trataCampo(temporario.sobreNome, 50);
        scanf("%s", temporario.eMail);
        trataCampo(temporario.eMail, 80);
        scanf("%s", temporario.nacionalidade);
        trataCampo(temporario.nacionalidade, 50);
        scanf("%d", &temporario.idade);

    }
}

void funcionalidade2() {

}

void funcionalidade3() {
    int rrn;
    scanf("%d", &rrn);

}

