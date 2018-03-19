

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

    i = 0;
    printf ("TESTING isGameOver():\n");
    for (i = 0; i <= 3; i++)
    {
        memset(&game, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, cards, seed, &game); // initialize a new game
        assert(r != -1); //check if initializeGame success
        memcpy(game.hand[i], cards, sizeof(int) * 10); // set all the cards to non-treasure card
        printf("--!!!!!!!\n");

        game.supplyCount[province] = i;
        game.supplyCount[i] = 0; // set empty pile

        if( i == 0 ){
#if (PRINTS == 1)
            printf("---------Test for i = %d. Expected result : game is over------------\n",i);
            r = 1;
#endif
        }
        else if( i == 3 ){
#if (PRINTS == 1)
            printf("---------Test for i = %d. Expected result : game is over------------\n",i);
            r = 1;
#endif
        }
        else{
#if (PRINTS == 1)
            printf("---------Test for i = %d. Expected result : game is NOT over---------\n",i);
            r = 0;
#endif
        }
        
        l = isGameOver(&game);
#if (PRINTS == 1)
        printf("check if the game is over...\n");
#endif
        assert(l == r);
#if (PRINTS == 1)
        printf("...PASSED\n");
#endif
        
    }

    printf("All tests passed!\n");

    return 0;
}
