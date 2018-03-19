

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 2000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState game, testGame;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, cards, seed, &game);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	printf("checking for +3 cards...\n");

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handpos, &bonus);

	newCards = 3;
	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testGame.handCount[thisPlayer], game.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testGame.deckCount[thisPlayer], game.deckCount[thisPlayer] - newCards + shuffledCards);

	if((testGame.handCount[thisPlayer] == game.handCount[thisPlayer] + newCards - discarded) && (testGame.deckCount[thisPlayer] == game.deckCount[thisPlayer] - newCards + shuffledCards))
		printf("...PASSED\n");
	else
		printf("...NOT PASSED\n");

	

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


