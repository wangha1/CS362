

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define PRINTS 1

int main() {
    int i, j, l, r;
    int seed = 2000;
    int numPlayer = 3;
    int maxBonus = 10;
    int cards[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState game;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
    i = 0;
    printf ("TESTING updateCoins():\n");
    for (i = 1; i <= numPlayer; i++)
    {
        for (j = 1; j <= maxHandCount; j++)
        {
            for (l = 0; l <= maxBonus; l++)
            {
                memset(&game, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, cards, seed, &game); // initialize a new game
                assert(r != -1); //check if initializeGame success

#if (PRINTS == 1)
                printf("Test no treasure card and %d bonus for player %d .\n",l , i);
#endif
                game.handCount[i] = j;                 // set the number of cards on hand
                memcpy(game.hand[i], cards, sizeof(int) * j); // set all the cards to non-treasure card
                updateCoins(i, &game, l);
#if (PRINTS == 1)
                printf("game.coins = %d, expected = %d\n", game.coins, l);
#endif


#if (PRINTS == 1)
                printf("Test player %d with %d treasure card(s) and %d bonus.\n", i, j, l);
#endif
                
                memcpy(game.hand[i], coppers, sizeof(int) * j); // set all the cards to copper
                updateCoins(i, &game, l);
#if (PRINTS == 1)
                printf("game.coins = %d, expected = %d\n", game.coins, j * 1 + l);
#endif
                assert(game.coins == j * 1 + l); // check if the number of coins is correct

                memcpy(game.hand[i], silvers, sizeof(int) * j); // set all the cards to silver
                updateCoins(i, &game, l);
#if (PRINTS == 1)
                printf("game.coins = %d, expected = %d\n", game.coins, j * 2 + l);
#endif
                assert(game.coins == j * 2 + l); // check if the number of coins is correct

                memcpy(game.hand[i], golds, sizeof(int) * j); // set all the cards to gold
                updateCoins(i, &game, l);
#if (PRINTS == 1)
                printf("game.coins = %d, expected = %d\n", game.coins, j * 3 + l);
#endif
                assert(game.coins == j * 3 + l); // check if the number of coins is correct
            }
        }
    }

    printf("All tests passed!\n");

    return 0;
}
