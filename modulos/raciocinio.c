#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char num[3];
    char cor[4];
}Carta;

void debugNum(int message) {
  fprintf(stderr, "%d\n", message);
}
void debug(char *message) {
  fprintf(stderr, "%s\n", message);
}
void debugChar(char message) {
  fprintf(stderr, "%c\n", message);
}
void showCard(Carta card) {
  fprintf(stderr, "%s%s ", card.cor, card.num);
}

// pega a string que é a mão e escreve uma carta num array de Carta
int getCards(int n, char* mao, int nC, Carta* listCards)
{
    int k = 0; // contador pra escrita do naipe
    for (int i = n; n < n+5; i++)
    {
//        debug("----i GETCARD-----");
//        debugNum(i);
        if (mao[i] == ' ')
        {
            listCards[nC].cor[3] = '\0';
            //debug("----ACHOU A CARTA----");
            //debug("----i GETCARD-----");
            //debugNum(i);
            //showCard(listCards[nC]);
            return i-n;
        }
        else if ((int) mao[i] > 49 && (int) mao[i] < 58)
        {
            listCards[nC].num[0] = mao[i];
            listCards[nC].num[1] = '\0';
        }
        else if (mao[i] == '1')
        {
            listCards[nC].num[0] = '1';
            listCards[nC].num[1] = '0';
            listCards[nC].num[2] = '\0';
            i++;
        }
        else if ((int) mao[i] > 64 && (int) mao[i] < 91) // se a carta for uma letra
        {
            listCards[nC].num[0] = mao[i];
            listCards[nC].num[1] = '\0';
        }
        else
        {
            listCards[nC].cor[k] = mao[i];
            k++;
        }
    }
    return 10; //se der erro vai pular tudo
}


int getHand(int size, char* mao, Carta* listCards)
{
    Carta mesa[1];
    int nC = 0;
    //char teste[100];

    //salva uma lista de cartas
    //debug("-----PROCURANDO MÃO-----");
    for (int i = 2; i < size-2; ++i)
    {
        //teste[i-2] = mao[i];
        //debug("----nC =");
        //debugNum(nC);
        if (mao[i] == ']')
            break;
        else if (mao[i] != ' ')
        {
            //debug("-----VAI CHAMAR O GETCARD-----");
            //debug("i mao=");
            //debugNum(i);
            //debugChar(mao[i]);
            //'debug("----i GETCARD-----");
            i += getCards(i, mao, nC, listCards);
            //debug("i mao=");
            //debugNum(i);
            nC++;
        }
    }
    debug("");
//    teste[strlen(mao)-3] = '\0';
//    debug("----TESTANDO A MAO ------");
//    debug(teste);
//    debug("----TESTE LEN MAO------");
//    debugNum(strlen(mao));
//    debug("----TESTE LEN MAO-teste----");
//    debugNum(strlen(teste));

    return nC;
}


void discard(Carta card, int nC, Carta* listCards)
{
    Carta temp[nC-1];
    int k = 0;
    for (int i = 0; i < nC; i++)
    {
        if (strcmp(card.cor, listCards[i].cor) == 1 && strcmp(card.num, listCards[i].num) == 1)
        {
            temp[k] = listCards[i]; 
            k++;
        }
    }
    for (int i = 0; i < nC-1; i++)
        listCards[i] = temp[i];
}


int pensaJogada(int nC, Carta mesa[1], Carta *listCards)
{
    int nCor=0, nNum=0;

    // conta o número de cartas da cor ou de número, pra ver o que tem mais e qual a melhor estratégia.
    for (int i = 0; i < nC; ++i)
    {
        //if (listCards[i].cor[0] == mesa[0].cor[0])
        if (strcmp(listCards[i].cor, mesa[0].cor) == 0)
            nCor++;

        //if (listCards[i].num == mesa[0].num)
        if (strcmp(listCards[i].num, mesa[0].num) == 0)
            nNum++;
    }
    debug("nCor e nNum");
    debugNum(nCor);
    debugNum(nNum);
    // avalia se vai por número ou vai por cor
    if (strcmp(mesa[0].num, "V") == 0)
    {
        printf("BUY 2\n");
        return nC + 2;
    }
    else if (strcmp(mesa[0].num, "C") == 0)
    {
        printf("BUY 4\n");
        return nC + 2;
    }
    else if (nCor == 0 && nNum == 0) // nesse caso vai comprar
    {
        printf("BUY 1\n");
        //return listCards[50];
        return nC + 1;
    }
    else if (nCor >= nNum)
    {
        for (int i = 0; i < nC; ++i)
            if (strcmp(listCards[i].cor, mesa[0].cor) == 0)
            {
                printf("DISCARD %s%s\n", listCards[i].num, listCards[i].cor);
                discard(listCards[i], nC, listCards);
                //return listCards[i];
                return nC - 1;
            }
    }
    else
    {
        for (int i = 0; i < nC; ++i)
            if (strcmp(listCards[i].num, mesa[0].num) == 0)
            {
                printf("DISCARD %s%s\n", listCards[i].num, listCards[i].cor);
                discard(listCards[i], nC, listCards);
                //return listCards[i];
                return nC - 1;
            }
    }
    //return listCards[0];
}
