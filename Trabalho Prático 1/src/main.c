#include <stdio.h>
#include "headerFuncoes.h"

int main(void){
    int funcionalidade; 
    scanf("%d", &funcionalidade);

    char nomeArqEntrada[campoMaximo];
    readline(nomeArqEntrada);

    char nomeArqSaida[campoMaximo];
    readline(nomeArqSaida);

    //printf("%d, %s, %s", funcionalidade, nomeArqEntrada, nomeArqSaida);

    switch(funcionalidade) {
        case 1:
            funcUm(nomeArqEntrada, nomeArqSaida);
            break;
        case 2:
            printf("Ainda nn fiz o SELECT \n");
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
