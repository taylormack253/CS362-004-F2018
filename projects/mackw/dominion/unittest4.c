///////////////////////////////////////////////////////////////////////
// File: unittest4.c
// Author: William Taylor Mack
// Description: Unit testing for whosTurn

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

//unit test 4 tests to check next player's turn
//this acts to check if another player is existant 
int main (int argc, char** argv)	{
    struct gameState G;
    int a;
	int k[10] = {adventurer, gardens, minion, village, embargo, mine, cutpurse, baron, tribute, smithy};
	
	printf ("\n** Unit Test 4: Who's turn is it? **\n");
	
	printf("\nRunning test 3 times because base game is set to 4 players\n");
	printf("Checking to see if other three players are still legal targets\n");
    for (int x = 2 ; x < 5 ; ++x)	{
        a = initializeGame(2, k, 5, &G);
        a = whoseTurn(&G);
        assert(a == G.whoseTurn);
		printf("Test Passed\n");		
	}

	printf("\n** End of Unit Test 4: Who's turn is it? **\n");

	return 0;
}