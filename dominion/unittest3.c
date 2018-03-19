
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
    int cardsCost[10] = {6, 5, 4, 4, 5
               , 4, 4, 3, 4, 3};
    struct gameState game;
    int maxHandCount = 5;

    i = 0;
    printf ("TESTING getCost():\n");
    for (i = 1; i <= numPlayer; i++)
    {
        for (j = 0; j < 10; j++)
        {
            
            memset(&game, 23, sizeof(struct gameState));   // clear the game state
            r = initializeGame(numPlayer, cards, seed, &game); // initialize a new game
            assert(r != -1); //check if initializeGame success
            game.handCount[i] = j;                 // set the number of cards on hand
            memcpy(game.hand[i], cards, sizeof(int) * j); // set all the cards to non-treasure card

#if (PRINTS == 1)
            printf("---------Test for player %d .---------\n",i);
#endif
            
            l = getCost(cards[j]);
#if (PRINTS == 1)
            printf("check if the costs are the same...\n");
#endif
#if (PRINTS == 1)
            printf("cost = %d, expected = %d", l, cardsCost[j]);
#endif
            assert(l == cardsCost[j]);
#if (PRINTS == 1)
            printf("...PASSED\n");
#endif
        }
    }

    printf("All tests passed!\n");

    return 0;
}
