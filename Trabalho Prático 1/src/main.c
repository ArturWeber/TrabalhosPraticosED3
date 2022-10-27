#include <stdio.h>
#include <stdlib.h>
#include "headerFuncoes.h"

int main(void){
    int funcionalidade; 
    //char *nomeArqEntrada;
    //char *nomeArqSaida;
    //scanf("%d %ms", &funcionalidade, &nomeArqEntrada);
    char nomeArqEntrada[campoMaximo];
    char nomeArqSaida[campoMaximo];
    scanf("%d %s", &funcionalidade, nomeArqEntrada);

    switch(funcionalidade) {
        case 1:
            //scanf("%ms", &nomeArqSaida);
            scanf("%s", nomeArqSaida);
            funcUm(nomeArqEntrada, nomeArqSaida);
            //free(nomeArqSaida);
            break;
        case 2:
            funcDois(nomeArqEntrada);
            break;
        case 3:
            funcTres(nomeArqEntrada);
            break;
        case 4:
            funcQuatro(nomeArqEntrada);
            break;
        case 5:
            funcCinco(nomeArqEntrada);
            break;
        case 6:
            printf("Ainda nn fiz a COMPACTACAO \n");
            break; 
        default:
            printf("Comando Não Encontrado \n");
    }

    //free(nomeArqEntrada);
    return 0;

}
