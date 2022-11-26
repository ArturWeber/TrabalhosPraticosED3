#include <stdio.h>
#include <string.h>

#include "funcoesGeraisT1.h"
#include "funcoesGeraisT2.h"
#include "funcoesBuscaBin.h"
#include "funcoesImpressaoBin.h"
#include "funcaoSete.h"
#include "funcaoNove.h"

//OBS: COLOCAR FUNCAO 9 JUNTO DA 7... MUITO PARECIDAS 
//INSERCAOARVORE.C 
//OU TACAR ENGINEINSERCAOINDICE E DEPENDENTES COMO FUNCOESGERAIS DO T2

void insertIntoIndice(FILE* arqEntrada, FILE* arqIndice, regCabecalho* cabecalho, regCabecalhoIndice* cabecalhoIndice) {
    //Le o numero de insercoes
    int numInsercoes;
    scanf("%d", &numInsercoes);

    registro aux[numInsercoes];
    char entrada[7][campoMaximo];
    for (int insercao = 0; insercao < numInsercoes; insercao++) {
        //Le cada um dos campos que se quer adicionar 
        for (int indice = 0; indice < 7; indice++) {
            if(temAspas(indice, 1)) {
                scan_quote_string(entrada[indice]);
            } else {
                scanf(" %s", entrada[indice]);
            }
            switch(indice){
                case 0:
                    aux[insercao].idConecta = gravaInt(entrada[indice]);
                    break;
                case 1:
                    strcpy(aux[insercao].nomePoPs, entrada[indice]);
                    break;
                case 2:
                    strcpy(aux[insercao].nomePais, entrada[indice]);
                    break;
                case 3:
                    strcpy(aux[insercao].siglaPais, entrada[indice]);
                    break;
                case 4:
                    aux[insercao].idPoPsConectado = gravaInt(entrada[indice]);
                    break;
                case 5:
                    aux[insercao].unidadeMedida = entrada[indice][0];
                    break;
                case 6:
                    aux[insercao].velocidade = gravaInt(entrada[indice]);
                break;
            }
        }
    }

    //Insere cada um dos campos
    int rrnInserir;
    for(int insercao = 0; insercao < numInsercoes; insercao++) {
        //Se houver espaco livre no meio do .bin, insere no meio e caso contrario insere no fim
        if(cabecalho->nroRegRem) {
            fseek(arqEntrada, (961 + (cabecalho->topo * 64)), SEEK_SET);
            rrnInserir = cabecalho->topo;
            fread(&(cabecalho->topo), sizeof(int), 1, arqEntrada);
            fseek(arqEntrada, -5, SEEK_CUR);
            insereRegistro(arqEntrada, aux[insercao]);   
            cabecalho->nroRegRem--;
        
        } else {
            fseek(arqEntrada, (960 + (cabecalho->proxRRN * 64)), SEEK_SET);
            insereRegistro(arqEntrada, aux[insercao]);
            rrnInserir = cabecalho->proxRRN;
            cabecalho->proxRRN++;
        }
            
        //INSERE NA ARVORE B 
        dado dadoInserir;
        engineInsercaoIndice(arqIndice, cabecalhoIndice, &aux[insercao], &dadoInserir, rrnInserir);
       
    }
    //Atualiza status cabecalho caso procedimento de certo
    cabecalho->status = '1';
    cabecalhoIndice->status = '1';
}
