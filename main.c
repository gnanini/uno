#include <stdio.h>
#include <string.h>

#include "./modulos/raciocinio.c"

/** Constantes para as strings a serem lidas */
#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10


int main() {
    char players[MAX_LINE];     // string para leitura temporária de dados
    char my_id[20];    // identificador do seu bot
    char hand[MAX_LINE];
    char mesa[6];

    setbuf(stdin, NULL);     // stdin, stdout e stderr não terão buffers
    setbuf(stdout, NULL);    // assim, nada é "guardado temporariamente"
    setbuf(stderr, NULL);

    scanf("PLAYERS %[^\n]\n", players);
    scanf("YOU %s\n", my_id);
    scanf("HAND %[^\n]\n", hand);
    scanf("TABLE %s\n", mesa);
    mesa[4] = ' ';
    mesa[5] = '\0';

    // === PARTIDA ===

    char id[MAX_ID_SIZE];
    char action[MAX_ACTION];
    char complement[12];
    char comp2[6];
    Carta cartaDaMesa[1]; // é a carta da mesa processada em nosso dataType
    Carta carta;
    char card[] = "A♥ ♥";
    int sizeHand;
    sizeHand = strlen(hand);
    Carta listCards[51];
    int nC; // numero de cartas
    int descartei = 0;

    nC = getHand(sizeHand, hand, listCards);
    for (int i = 0; i < nC; i++)
        showCard(listCards[i]);
    debug("");

    while(1) {
        do {
            scanf("%s %[^\n]", action, complement);
            if (strcmp(action,"DISCARD") == 0)
            {
                descartei = 0;
                if (complement[0] == 'A')
                {
                    for (int i = 5; i < 9; i++)
                        comp2[i-5] = complement[i];
                    for (int i = 1; i < 6; i++)
                        complement[i] = comp2[i-1];
                    debug("----A-na-mesa----");
                    debug(complement);
                }
                else if (complement[0] == 'C')
                {
                    for (int i = 5; i < 9; i++)
                        comp2[i-5] = complement[i];
                    for (int i = 1; i < 6; i++)
                        complement[i] = comp2[i-1];
                    debug("----C-na-mesa----");
                    debug(complement);
                }
                for (int i = 0; i < 6; i++)
                    mesa[i] = complement[i];
            }
        } while (strcmp(action, "TURN") || strcmp(complement, my_id));

        // agora é a vez do seu bot jogar
        debug("----- MINHA VEZ -----");
        mesa[5] = ' ';
        if (descartei == 0)
        {
            debug("___GETCARDS da mesa___");
            getCards(0, mesa, 0, cartaDaMesa);
            showCard(cartaDaMesa[0]);
            debug("");
        }
        nC = pensaJogada(nC, cartaDaMesa, listCards, &descartei);
    }
    return 0;
}
