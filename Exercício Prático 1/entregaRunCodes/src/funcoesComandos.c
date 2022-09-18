#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

//Função responsável por preencher os bytes não utilizados no campo com lixo por tratarmos campos fixos
void trataCampo(char campo[], int capacidade) {
    int tamanho;
    //verifica o numero de bytes que foram preenchidos e compara se é menor que a capacidade maxima
    if (strlen(campo) < capacidade) {
        tamanho = strlen(campo);
    } else {
        tamanho = capacidade - 1;
    }

    //coloca o \0 onde a string acabou, mesmo que tenha sido usado todos os bytes, um será armazanado para o null
    campo[tamanho] = '\0'; 

    //adiciona lixo em bytes não preenchido no campo
    for (int i = (tamanho + 1); i < capacidade; i++){
        campo[i] = '$';
    }
    return;
}

void funcionalidade1(FILE* ponteiroArq) {
    int numReg;
    scanf("%d", &numReg);

    //cria e grava campos em um registro aux, depois gravando os registro obtidos um a um 
    //uma abordagem de armazenamento de todos os registros em memoria e depois em armazenamento poderia ter sido tomada com a vantagem de maior velocidade, porem mais uso de RAM
    pessoa aux;
    //laço da quantidade de registros
    for(int i = 0; i < numReg; i++){
        //input de cada um dos campos do registro armazenando-os na estrutura do tipo pessoa e chamando função para colocar o lixo nos bytes não utilizados do campo:
        scanf("%s", aux.primeiroNome);
        trataCampo(aux.primeiroNome, NOME_TAMANHO);
        scanf("%s", aux.sobreNome);
        trataCampo(aux.sobreNome, SOBRENOME_TAMANHO);
        scanf("%s", aux.eMail);
        trataCampo(aux.eMail, EMAIL_TAMANHO);
        scanf("%s", aux.nacionalidade);
        trataCampo(aux.nacionalidade, NACIONALIDADE_TAMANHO);
        scanf("%d", &aux.idade);

        //escrevendo os registros nos arquivos binários
        fwrite(aux.primeiroNome, sizeof(char), NOME_TAMANHO, ponteiroArq);
        fwrite(aux.sobreNome, sizeof(char), SOBRENOME_TAMANHO, ponteiroArq);
        fwrite(aux.eMail, sizeof(char), EMAIL_TAMANHO, ponteiroArq);
        fwrite(aux.nacionalidade, sizeof(char), NACIONALIDADE_TAMANHO, ponteiroArq);
        fwrite(&aux.idade, sizeof(int), 1, ponteiroArq);
    }
    return;
}


void funcionalidade2(FILE* ponteiroArq) {
    pessoa aux;
    //laço com condição de rodar até o arquivo acabar, ou seja não ter nada em primeiroNome, lendo todos os campos de todos os registros
    while(fread(aux.primeiroNome, sizeof(char), NOME_TAMANHO, ponteiroArq) != 0){
        //lendo campos
        fread(aux.sobreNome, sizeof(char), SOBRENOME_TAMANHO, ponteiroArq);
        fread(aux.eMail, sizeof(char), EMAIL_TAMANHO, ponteiroArq);
        fread(aux.nacionalidade, sizeof(char), NACIONALIDADE_TAMANHO, ponteiroArq);
        fread(&aux.idade, sizeof(int), 1, ponteiroArq);
        
        //imprime os campos na tela que foram armazenados na estrutura do tipo pessoa
        printf("Firstname: %s\n", aux.primeiroNome);
        printf("Lastname: %s\n", aux.sobreNome);
        printf("Email: %s\n", aux.eMail);
        printf("Nationality: %s\n", aux.nacionalidade);
        printf("Age: %d\n\n", aux.idade);
    }
    return;
}


void funcionalidade3(FILE* ponteiroArq) {
    int rrn;
    scanf("%d", &rrn);

    int tamanhoRegistro = NOME_TAMANHO + SOBRENOME_TAMANHO + EMAIL_TAMANHO + NACIONALIDADE_TAMANHO + 4;
    int byteOffset = tamanhoRegistro * rrn;
    fseek(ponteiroArq, byteOffset, SEEK_SET);

    pessoa aux;
    
    //se houver alguma coisa no arquivo no registro pesquisado ele lerá todos os campos do registro, armazenará os dados do campo em determinadas parte da estrutura do tipo pessoa 
    if(fread(aux.primeiroNome, sizeof(char), NOME_TAMANHO, ponteiroArq) != 0) {
        fread(aux.sobreNome, sizeof(char), SOBRENOME_TAMANHO, ponteiroArq);
        fread(aux.eMail, sizeof(char), EMAIL_TAMANHO, ponteiroArq);
        fread(aux.nacionalidade, sizeof(char), NACIONALIDADE_TAMANHO, ponteiroArq);
        fread(&aux.idade, sizeof(int), 1, ponteiroArq);
        //imprime os campos na tela que foram armazenados na estrutura do tipo pessoa
        printf("Firstname: %s\n", aux.primeiroNome);
        printf("Lastname: %s\n", aux.sobreNome);
        printf("Email: %s\n", aux.eMail);
        printf("Nationality: %s\n", aux.nacionalidade);
        printf("Age: %d\n\n", aux.idade);
    } else {
        printf("Não foi possível ler o arquivo");
        exit(0);
    }
    return;

}