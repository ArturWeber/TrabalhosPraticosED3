#include <stdio.h>
#include "headerFuncoes.h"

int main(void){
    int funcionalidade; 
    char nomeArqEntrada[campoMaximo];
    char nomeArqSaida[campoMaximo];
    scanf("%d %s ", &funcionalidade, nomeArqEntrada);

    //readline(nomeArqEntrada);


    switch(funcionalidade) {
        case 1:
            //readline(nomeArqSaida);
            scanf("%s", nomeArqSaida);
            funcUm(nomeArqEntrada, nomeArqSaida);
            break;
        case 2:
            //funcDois(nomeArqEntrada);
            break;
        case 3:
            printf("Ainda nn fiz o WHERE \n");
            break;
        case 4:
            printf("Ainda nn fiz a REMOCAO \n");
            break;
        case 5:
            printf("Ainda nn fiz o INSERT INTO \n");
            break;
        case 6:
            printf("Ainda nn fiz a COMPACTACAO \n");
            break; 
        default:
            printf("Comando Não Encontrado \n");
    }
}
