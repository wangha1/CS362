
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int actions = 0;
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

	printf("Checking for +1 cards...\n");

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &testGame, handpos, &bonus);

	newCards = 1;
	xtraCoins = 0;
	printf("Hand count = %d, expected = %d\n", testGame.handCount[thisPlayer], game.handCount[thisPlayer] + newCards - discarded);
	printf("Deck count = %d, expected = %d\n", testGame.deckCount[thisPlayer], game.deckCount[thisPlayer] - newCards + shuffledCards);

	if((testGame.handCount[thisPlayer] == game.handCount[thisPlayer] + newCards - discarded) && (testGame.deckCount[thisPlayer] == game.deckCount[thisPlayer] - newCards + shuffledCards))
		printf("...PASSED\n");
	else
		printf("...NOT PASSED\n");

	printf("Checking for +2 actions...\n");

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));
	cardEffect(steward, choice1, choice2, choice3, &testGame, handpos, &bonus);

	newCards = 0;
	actions = 2;
	printf("Actions = %d, expected = %d\n", testGame.numActions, game.numActions + actions);

	if((testGame.numActions == game.numActions + 2))
		printf("...PASSED\n");
	else
		printf("...NOT PASSED\n");

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


