#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./raciocinio.c"



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
    debug("-----DISCARD----");
    showCard(card);

    printf("DISCARD %s%s\n", card.num, card.cor);
    debugNum(nC);
    for (int i = 0; i < nC; i++)
    {
        if (strcmp(card.cor, listCards[i].cor) == 1 || strcmp(card.num, listCards[i].num) == 1)
        {
            debugNum(i);
            showCard(listCards[i]);
            temp[k] = listCards[i]; 
            k++;
        }
    }
    for (int i = 0; i < nC-1; i++)
    {
        listCards[i] = temp[i];
        //debugChar(listCards[i].num[0]);
        //debug(listCards[i].cor);
    }
}


int compraCarta(int n, int nC, Carta* listCards)
{
    char strcarta[n][6];
    Carta cards[n];
    debug("-----COMPRA CARTA----");
    printf("BUY %d/n", n);
    for (int i = 0; i < n; i++)
    {
        scanf(" %s", strcarta[i]);
        debug(strcarta[i]);
    }
    for (int i = nC; i < nC + n; i++)
        listCards[i] = cards[i-nC];
    return nC-n;
}


