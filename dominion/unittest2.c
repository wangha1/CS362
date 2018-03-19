

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define PRINTS 1

int main() {
    int count, count2;
    int i, j, l, r;
    int seed = 2000;
    int numPlayer = 3;
    int maxBonus = 10;
    int cards[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState game;
    struct gameState game2;
    int maxHandCount = 5;

    i = 0;
    printf ("TESTING discardCard():\n");
    for (i = 1; i <= numPlayer; i++)
    {
        for (j = 1; j <= maxHandCount; j++)
        {
            
            memset(&game, 23, sizeof(struct gameState));   // clear the game state
            r = initializeGame(numPlayer, cards, seed, &game); // initialize a new game
            assert(r != -1); //check if initializeGame success
            r = initializeGame(numPlayer, cards, seed, &game2); // initialize a new game
            assert(r != -1); //check if initializeGame success
            for (l = 0; l < j; l++)
            {
/*************************** trashed(game) *************************************/
                game.handCount[i] = j;                 // set the number of cards on hand
                memcpy(game.hand[i], cards, sizeof(int) * j); // set all the cards to non-treasure card
                count = 0;

#if (PRINTS == 1)
                printf("---------Test if the card is trashed for player %d, card position %d .------------\n",i, l);
#endif
                
                discardCard(l, i, &game, 1);
#if (PRINTS == 1)
                printf("check if the last card is set to -1");
#endif
                assert(game.hand[i][j-1] == -1);
#if (PRINTS == 1)
                printf("...PASSED\n");
#endif
#if (PRINTS == 1)
                printf("check if the card is NOT in played pile");
#endif
                assert(game.playedCardCount == 0);
#if (PRINTS == 1)
                printf("...PASSED\n");
#endif

#if (PRINTS == 1)
                printf("check the number of cards in hand is reduced");
#endif
                assert(game.handCount[i] == j-1);
#if (PRINTS == 1)
                printf("...PASSED\n");
#endif

/*************************** NOT trashed(game2) *************************************/
                game2.handCount[i] = j;                 // set the number of cards on hand
                memcpy(game2.hand[i], cards, sizeof(int) * j); // set all the cards to non-treasure card
                count2 = game2.playedCardCount;
                count2++;

#if (PRINTS == 1)
                printf("---------Test if the card is NOT trashed for player %d, card position %d .---------\n",i, j);
#endif
                
                discardCard(l, i, &game2, 0);
#if (PRINTS == 1)
                printf("check if the last card is set to -1");
#endif
                assert(game2.hand[i][j-1] == -1);
#if (PRINTS == 1)
                printf("...PASSED\n");
#endif
#if (PRINTS == 1)
                printf("check if the card is in played pile");
#endif
                assert(game2.playedCardCount == count2);
#if (PRINTS == 1)
                printf("...PASSED\n");
#endif

#if (PRINTS == 1)
                printf("check the number of cards in hand is reduced");
#endif
                assert(game2.handCount[i] == j-1);
#if (PRINTS == 1)
                printf("...PASSED\n");
#endif
            }
        }
    }

    printf("All tests passed!\n");

    return 0;
}
