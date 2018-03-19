
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"
#define PLAYNUM 1000

int main() {
	int passed = 0;
	int notPassed = 0;
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int actions = 0;
    int shuffledCards = 0;
    srand(time(NULL));
    int i, j, m, r;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 2000;
    int numPlayer = 2;
    int thisPlayer = 0;
	struct gameState game, testGame;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int card[3] = {estate, duchy, province};
	
	for (i = 1; i <= PLAYNUM; i++){
		
		// initialize a game state and player cards
		memset(&game, 23, sizeof(struct gameState));   // clear the game state
		numPlayer = (rand() % 3) + 2; // set random player number
		seed = rand(); // set random seed
	    r = initializeGame(numPlayer, cards, seed, &game); // initialize a new game
	    assert(r != -1); //check if initializeGame success;



		printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

		printf("---Checking for adventurer cards......---\n");

		// copy the game state to a test case
		//game.hand[thisPlayer][handPos] = adventurer;
		memcpy(&testGame, &game, sizeof(struct gameState));
		// give card
		testGame.hand[thisPlayer][testGame.handCount[thisPlayer]] = adventurer;
		testGame.handCount[thisPlayer]++;
		assert(game.handCount[thisPlayer] + 1 == testGame.handCount[thisPlayer]);

		cardEffect(adventurer, choice1, choice2, choice3, &testGame, handpos, &bonus);

		printf("Checking for treasure cards from drawn cards......\n");

		if(testGame.hand[thisPlayer][testGame.handCount[thisPlayer] - 2] == copper || testGame.hand[thisPlayer][testGame.handCount[thisPlayer] - 2] == silver || testGame.hand[thisPlayer][testGame.handCount[thisPlayer] - 2] == gold){
			printf("......PASSED\n");
			passed++;
		}
		else{
			printf("......NOT PASSED\n");
			notPassed++;
		}
	
		if(testGame.hand[thisPlayer][testGame.handCount[thisPlayer] - 1] == copper || testGame.hand[thisPlayer][testGame.handCount[thisPlayer] - 1] == silver || testGame.hand[thisPlayer][testGame.handCount[thisPlayer] - 1] == gold){
			printf("......PASSED\n");
			passed++;
		}
		else{
			printf("......NOT PASSED\n");
			notPassed++;
		}

		printf("Checking for number of cards in hand......\n");
		printf("Count = %d, expected = %d\n", testGame.handCount[thisPlayer], game.handCount[thisPlayer] + 2);
		if(testGame.handCount[thisPlayer] - 2 == game.handCount[thisPlayer])
        {
        	printf("......PASSED\n");
        	passed++;
        }
		else{
			printf("......NOT PASSED\n");
			notPassed++;
		}

		printf("Checking for number of cards in deck......\n");
		printf("Count = %d, expected = %d\n", testGame.deckCount[thisPlayer], game.deckCount[thisPlayer] - 2);
		if(testGame.deckCount[thisPlayer] + 2 == game.deckCount[thisPlayer])
        {
        	printf("......PASSED\n");
        	passed++;
        }
		else{
			printf("......NOT PASSED\n");
			notPassed++;
		}

		printf("Checking for in-hand cards of other players......\n");
		for(m = 1; m < numPlayer; m++){
			printf("Count = %d, expected = %d\n", testGame.handCount[m], game.handCount[m]);
			if(testGame.handCount[m] == game.handCount[m])
	        {
	        	printf("......PASSED\n");
	        	passed++;
	        }
			else
{
	printf("......NOT PASSED\n");
	notPassed++;
}
		}

		printf("Checking for decks of other players......\n");
		for(m = 1; m < numPlayer; m++){
			printf("Count = %d, expected = %d\n", testGame.deckCount[m], game.deckCount[m]);
			if(testGame.deckCount[m] == game.deckCount[m])
	        {
	        	printf("......PASSED\n");
	        	passed++;
	        }
			else
{
	printf("......NOT PASSED\n");
	notPassed++;
}
		}

		printf("Checking for victory pile......\n");
		for(m = 0; m < 3; m++){
			printf("Count = %d, expected = %d\n", testGame.supplyCount[card[m]], game.supplyCount[card[m]]);
			if(testGame.supplyCount[card[m]] == game.supplyCount[card[m]])
	        {
	        	printf("......PASSED\n");
	        	passed++;
	        }
			else
{
	printf("......NOT PASSED\n");
	notPassed++;
}
		}


	}
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n", TESTCARD);
	printf(" >>>>> PASSED: %d, NOT PASSED: %d <<<<<\n\n", passed, notPassed);


	return 0;
}


