/************************************************************
 *            Trabalho Prático 2 - SCC0607                   *
 *                                                           *
 *      Nome: Artur Brenner Weber                            *
 *      nUSP: 12675451    Participacao: 100%                 *
 *      Nome: Aruan  Bretas de Oliveira Filho                *
 *      nUSP: 12609731    Participacao: 100%                  *
 *      Data de última atualizacao: 25/11/2022               *
 *      Ambiente de Desenvolv: VSCode 1.73.1                 *
 *                                                           *
 *             Conteudo arquivo funcoesBuscaBin:             *
 *   Funcoes secundarias das funcionalidades                 *
 *         7 (createIndex) e 9 (InsertIntoIndex)             *
 * Organizadas juntas pois envolvem funcoes em comum.        *
*************************************************************/

#include <stdio.h>
#include <string.h>

#include "funcoesGeraisT1.h"
#include "funcoesGeraisT2.h"
#include "funcoesBuscaBin.h"
#include "funcoesImpressaoBin.h"
#include "insercaoArvore.h"


//Aplica os valores do cabecalho passado como parametro ao arquivo de indice .bin 
void atualizaRegCabecalhoIndice (FILE* arquivo, regCabecalhoIndice cabecalho) {
    fseek(arquivo, 0L, SEEK_SET);

	fwrite(&cabecalho.status, sizeof(char), 1, arquivo);
    fwrite(&cabecalho.noRaiz, sizeof(int), 1, arquivo);
	fwrite(&cabecalho.nroChavesTotal, sizeof(int), 1, arquivo);
    fwrite(&cabecalho.alturaArvore, sizeof(int), 1, arquivo);
    fwrite(&cabecalho.RRNproxNo, sizeof(int), 1, arquivo);

    preenchimentoComSifrao(arquivo, 17, 65);

}

//Funcao do tipo regCabecalhoIndice que inicializa o cabecalho do indice 
//com valores iniciais especificados no documento
regCabecalhoIndice inicializaCabecalhoIndice(void) {
    regCabecalhoIndice aux;
    memset(&aux, 0, sizeof(regCabecalhoIndice));

    aux.status = '0';
    aux.noRaiz = -1;
    aux.nroChavesTotal = 0;
    aux.alturaArvore = 0;
    aux.RRNproxNo = 0;
    return aux;
}

//Funcionalidade que insere o No no arquivo de indice .bin
void salvarNo(FILE *arquivo, registroIndice aux) {
    fseek(arquivo, (aux.RRNdoNo + 1) * 65, SEEK_SET);

    fwrite(&aux.folha, sizeof(char), 1, arquivo);
	fwrite(&aux.nroChavesNo, sizeof(int), 1, arquivo);
	fwrite(&aux.alturaNo, sizeof(int), 1, arquivo);
	fwrite(&aux.RRNdoNo, sizeof(int), 1, arquivo);
    for (int i = 0; i < ordemArvore - 1; i++) {
	    fwrite(&aux.ponteiros[i], sizeof(int), 1, arquivo); 
        fwrite(&aux.dados[i].chave, sizeof(int), 1, arquivo);
        fwrite(&aux.dados[i].referencia, sizeof(int), 1, arquivo);
    }
    fwrite(&aux.ponteiros[ordemArvore - 1], sizeof(int), 1, arquivo);

}

//Inicializa um No do zero na arvore
registroIndice criaNovoNo(char folha, int nroChavesNo, int alturaNo, int RRNdoNo) {
    // cria um novo no do zero
    registroIndice novoNo;
    memset(&novoNo, -1, sizeof(registroIndice));

    novoNo.folha = folha;
    novoNo.nroChavesNo = nroChavesNo;
    novoNo.alturaNo = alturaNo;
    novoNo.RRNdoNo = RRNdoNo;
    for(int i = 0; i < ordemArvore; i++) {
        novoNo.ponteiros[i] = -1;
    }
    for(int i = 0; i < ordemArvore - 1; i++) {
        novoNo.dados[i].chave = -1;
        novoNo.dados[i].referencia = -1;
    }
    return novoNo;
}

//Funcionalidade responsável por fazer o split, ou seja, quando houver a necessidade
//de criar um novo No dentro da arvore
registroIndice split(registroIndice* noAtual, dado* dadoInserir, int *ponteiroInserir, regCabecalhoIndice* cabecalhoIndice) {
    int posInserir = posicaoInserir(*noAtual, dadoInserir->chave);
    dado todosDados[ordemArvore];
    int todosPonteiros[ordemArvore + 1];
    todosPonteiros[0] = noAtual->ponteiros[0];
    int j = 0;
    for(int i = 0; i < ordemArvore; i++) {
        if (i == posInserir) {
            todosDados[i] = *dadoInserir;
            todosPonteiros[i + 1] = *ponteiroInserir;
        } else {
            todosDados[i] = noAtual->dados[j];
            todosPonteiros[i + 1] = noAtual->ponteiros[j + 1];
            j++;
        }
    }

    dado dadoVazio; 
    dadoVazio.chave = -1;
    dadoVazio.referencia = -1;

    int numChavesNo = ordemArvore / 2;
    registroIndice novoNo = criaNovoNo(noAtual->folha, numChavesNo, noAtual->alturaNo, cabecalhoIndice->RRNproxNo);
    cabecalhoIndice->RRNproxNo++;

    noAtual->ponteiros[0] = todosPonteiros[0];
    for (int i = 0; i < numChavesNo; i++) {
        noAtual->dados[i] = todosDados[i];
        noAtual->ponteiros[i + 1] = todosPonteiros[i + 1];
    }
    for (int i = numChavesNo; i < ordemArvore - 1; i++) {
        //limpa os repetidos do noAtual 
        noAtual->dados[i] = dadoVazio;
        noAtual->ponteiros[i + 1] = -1;
    }
    noAtual->nroChavesNo = numChavesNo;
    
    novoNo.ponteiros[0] = todosPonteiros[numChavesNo + 1];
    for (int i = 0; i < numChavesNo; i++) {
        novoNo.dados[i] = todosDados[i + 1 + numChavesNo];
        novoNo.ponteiros[i + 1] = todosPonteiros[i + 2 + numChavesNo];
    }
    novoNo.nroChavesNo = numChavesNo;

    *ponteiroInserir = novoNo.RRNdoNo;
    *dadoInserir = todosDados[numChavesNo];

    return novoNo;
}

//Funcao responsavel pela insercao de um dado a ser inserido no arquivo de indice,
//verificar se ha necessidade de split
//e chamar a funcao para salvar os dados no arquivo de indice .bin
void insereRegistroIndice(FILE* arqSaida, dado* dadoInserir, int *ponteiroInserir, regCabecalhoIndice* cabecalhoIndice, int RRNnoAtual) {
    //le o no atual
    registroIndice noAtual = leRegistroIndice(arqSaida, RRNnoAtual);

    //busca onde inserir recursivamente
    if (noAtual.folha == '0') {
        //Continua buscando onde inserir
        int posPonteiro = posicaoInserir(noAtual, dadoInserir->chave);
        int RRNfilho = noAtual.ponteiros[posPonteiro];
        insereRegistroIndice(arqSaida, dadoInserir, ponteiroInserir, cabecalhoIndice, RRNfilho);
    }
    //vai voltando na arvore verificando se tem que inserir elementos promovidos ou nao 
    if (dadoInserir->chave != -1) {
        if (noAtual.nroChavesNo < ordemArvore - 1) {
            //tem espaco
            //procura onde inserir
            int posInserir = posicaoInserir(noAtual, dadoInserir->chave);
            for (int i = noAtual.nroChavesNo; i > posInserir; i--) {
                noAtual.dados[i] = noAtual.dados[i - 1];
                noAtual.ponteiros[i + 1] = noAtual.ponteiros[i];
            }
            noAtual.dados[posInserir] = *dadoInserir;
            noAtual.ponteiros[posInserir + 1] = *ponteiroInserir;
            noAtual.nroChavesNo++;
            //Nao ha mais dados a inserir
            dadoInserir->chave = -1;
            dadoInserir->referencia = -1;
        } else {
            //nao tem mais espaco
            //faz o split e promove!
            registroIndice novoNo = split(&noAtual, dadoInserir, ponteiroInserir, cabecalhoIndice);
            salvarNo(arqSaida, novoNo);
        }
        salvarNo(arqSaida, noAtual);
    }
}

//Funcao que cria a raiz da arvore ou faz o split para criacao de uma nova raiz
void engineInsercaoIndice(FILE* arqSaida, regCabecalhoIndice* cabecalhoIndice, registro* registroInserir, dado *dadoInserir, int rrn){
    if (cabecalhoIndice->noRaiz == -1) {
        //se a arvore ainda nao tem nenhum no 
        //cria raiz inicial 
        registroIndice primeiraRaiz = criaNovoNo('1', 0, 1, cabecalhoIndice->RRNproxNo);
        //atualiza cabecalho com novos valores da raiz, atualiza RRNproxNo e aumenta a altura da arvore 
        cabecalhoIndice->noRaiz = cabecalhoIndice->RRNproxNo;
        cabecalhoIndice->RRNproxNo++;
        cabecalhoIndice->alturaArvore++;
        salvarNo(arqSaida, primeiraRaiz);
        
    }

    //prepara o dado para ser inserido
    dadoInserir->chave = registroInserir->idConecta;
    dadoInserir->referencia = rrn;
    int ponteiroInserir = -1;
    insereRegistroIndice(arqSaida, dadoInserir, &ponteiroInserir, cabecalhoIndice, cabecalhoIndice->noRaiz);

    //SE O DadoInserir CONTINUAR SENDO DIFERENTE DE -1, ENTAO HOUVE SPLIT NA ANTIGA RAIZ E TEMOS QUE CRIAR UMA NOVA RAIZ
    if (dadoInserir->chave != -1) {
        registroIndice novaRaiz = criaNovoNo('0', 1, cabecalhoIndice->alturaArvore + 1, cabecalhoIndice->RRNproxNo);
        novaRaiz.ponteiros[0] = cabecalhoIndice->noRaiz;
        novaRaiz.dados[0] = *dadoInserir;
        novaRaiz.ponteiros[1] = ponteiroInserir;
        salvarNo(arqSaida, novaRaiz);

        cabecalhoIndice->noRaiz = cabecalhoIndice->RRNproxNo;
        cabecalhoIndice->RRNproxNo++;
        cabecalhoIndice->alturaArvore++;
    }
    cabecalhoIndice->nroChavesTotal++;
}

//Funcao sencudaria da funcionalidade 7, cria o arquivo de indice com base no arquivo de dados
void createIndex(FILE* arqEntrada, FILE* arqSaida, regCabecalho cabecalho, regCabecalhoIndice* cabecalhoIndice){
    int encadeamento;
    char removido;
    
    //Le todo o lixo do cabecalho para mover ponteiro e em seguida le registro a registro e imprime
    leLixo(arqEntrada, 939);
    for(int rrn = 0; rrn < cabecalho.proxRRN; rrn++){

        fread(&removido, sizeof(char), 1, arqEntrada);
        //Se for removido nao adiciona ao indice
        if(removido == '1'){
            leLixo(arqEntrada, 63);
            continue;
        }

        //Senao, le registro e armazena no auxiliar
        registro registroInserir = inicializaRegistro();
        fread(&encadeamento, sizeof(int), 1, arqEntrada);
        //le todos os campos de um registro
        leRegistro(arqEntrada, &registroInserir);
        
        
        dado dadoInserir;
        engineInsercaoIndice(arqSaida, cabecalhoIndice, &registroInserir, &dadoInserir, rrn);
        
        //Le lixo do registro para mover ponteiro
        int comprimentoLixo = 42 - strlen(registroInserir.nomePoPs) - strlen(registroInserir.nomePais);
        leLixo(arqEntrada, comprimentoLixo);
    }

    cabecalhoIndice->status = '1';
}

//Funcao sencudaria da funcionalidade 9, insere novos registros no arquivo de dados
//e insere o indice desses novos registros adicionados no arquivo de indice
void insertIntoIndice(FILE* arqEntrada, FILE* arqIndice, regCabecalho* cabecalho, regCabecalhoIndice* cabecalhoIndice) {
    //Le o numero de insercoes
    int numInsercoes;
    scanf("%d", &numInsercoes);

    registro aux[numInsercoes];
    char entrada[7][campoMaximo];

    gravaParaInserir(entrada, numInsercoes, aux);

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
