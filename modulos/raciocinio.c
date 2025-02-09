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
        if (mao[i] == ' ')
        {
            listCards[nC].cor[3] = '\0';
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

    for (int i = 2; i < size-2; ++i)
    {
        if (mao[i] == ']')
            break;
        else if (mao[i] != ' ')
        {
            i += getCards(i, mao, nC, listCards);
            nC++;
        }
    }
    debug("");
    return nC;
}


int escolheNaipe(int nC, Carta *listCards)
{
    int naipes[4] = {0};
    int x = 0;
    for (int i = 0; i < nC; i++)
    {
        if (strcmp("♥", listCards[i].cor) == 0)
            naipes[0]++;
        else if (strcmp("♦", listCards[i].cor) == 0)
            naipes[1]++;
        else if (strcmp("♣", listCards[i].cor) == 0)
            naipes[2]++;
        else if (strcmp("♠", listCards[i].cor) == 0)
            naipes[3]++;
    }
    for (int i = 0; i < 4; i++)
        if (naipes[i] >= naipes[i+1])
            x = i;
    return x;
}


void discard(Carta card, int nC, Carta* listCards, Carta* mesa)
{
    char naipes[][4] = {"♥","♦","♣","♠"};
    Carta temp[nC-1];
    int k = 0;
    debug("-----DISCARD----");
    showCard(card);
    debug("");
    debug("----MÃO-ATUAL----");
    for (int i = 0; i < nC; i++)
    {
        if (strcmp(card.cor, listCards[i].cor) != 0 || strcmp(card.num, listCards[i].num) != 0)
        {
            temp[k] = listCards[i]; 
            k++;
        }
    }
    for (int i = 0; i < nC-1; i++)
    {
        listCards[i] = temp[i];
        showCard(listCards[i]);
    }
    mesa[0] = card;
    if (card.num[0] == 'A' || card.num[0] == 'C')
    {
        k = escolheNaipe(nC, listCards);
        for (int i = 0; i < 4; i++)
            mesa[0].cor[i] = naipes[k][i];
        printf("DISCARD %s%s %s\n", card.num, card.cor, naipes[k]);
    }
    else
        printf("DISCARD %s%s\n", card.num, card.cor);
}


int compraCarta(int n, int nC, Carta* listCards)
{
    char strcarta[10];
    Carta cards[n];
    debug("-----COMPRA CARTA----");
    printf("BUY %d\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf(" %s", strcarta);
        if (strcarta[0] == '1')
        {
            listCards[nC].num[0] = '1';
            listCards[nC].num[1] = '0';
            listCards[nC].num[2] = '\0';
            for (int i = 0; i < 3; i++)
                listCards[nC].cor[i] = strcarta[2 + i];
            listCards[nC].cor[3] = '\0';
        }
        else
        {
            listCards[nC].num[0] = strcarta[0];
            listCards[nC].num[1] = '\0';
            for (int i = 0; i < 3; i++)
                listCards[nC].cor[i] = strcarta[1 + i];
            listCards[nC].cor[3] = '\0';
        }
        showCard(listCards[nC]);
        debug("");
        nC++;
    }
    for (int i = nC; i < nC + n; i++)
        listCards[i] = cards[i-nC];
    return nC;
}


int usaEspeciais(int nC, Carta* listCards, Carta mesa)
{
    int k = 0;
    char naipes[][4] = {"♥","♦","♣","♠"};

    for (int i = 0; i < nC; i++)
        if ((listCards[i].num[0] == 'C' || listCards[i].num[0] == 'V' || listCards[i].num[0] == 'D' || listCards[i].num[0] == 'R') && (strcmp(listCards[i].cor, mesa.cor) == 0))
            return i;
    return -1;
}


int pensaJogada(int nC, Carta mesa[1], Carta *listCards, int* descartei)
{
    int nCor=0, nNum=0, especial=-1;
    // conta o número de cartas da cor ou de número, pra ver o que tem mais e qual a melhor estratégia.
    especial = usaEspeciais(nC, listCards, mesa[0]);
    for (int i = 0; i < nC; ++i)
    {
        if (strcmp(listCards[i].cor, mesa[0].cor) == 0)
            nCor++;
    if (strcmp(listCards[i].num, mesa[0].num) == 0)
            nNum++;
    }
    debug("----nNaipe-e-nNum----");
    debugNum(nCor);
    debugNum(nNum);

    // avalia se vai por número ou vai por cor
    if (strcmp(mesa[0].num, "V") == 0 && *descartei == 0)
    {
        nC = compraCarta(2, nC, listCards);
        return nC;
    }
    else if (strcmp(mesa[0].num, "C") == 0 && *descartei == 0)
    {
        nC = compraCarta(4, nC, listCards);
        return nC;
    }
    else if (nCor == 0 && nNum == 0) // nesse caso vai comprar
    {
        nC = compraCarta(1, nC, listCards);
        return nC;
    }
    else if (especial > -1)
    {
        discard(listCards[especial], nC, listCards, mesa);
        *descartei = 1;
        return nC-1;
    }
    else if (nCor >= nNum)
    {
        for (int i = 0; i < nC; ++i)
            if (strcmp(listCards[i].cor, mesa[0].cor) == 0)
            {
                discard(listCards[i], nC, listCards, mesa);
                *descartei = 1;
                return nC - 1;
            }
    }
    else
    {
        for (int i = 0; i < nC; ++i)
            if (strcmp(listCards[i].num, mesa[0].num) == 0)
            {
                discard(listCards[i], nC, listCards, mesa);
                *descartei = 1;
                return nC - 1;
            }
    }
    return nC;
}
