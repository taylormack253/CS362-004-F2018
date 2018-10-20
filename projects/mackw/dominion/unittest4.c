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
#define NO_CARDS 0
#define NUM_CARDS 27
#define TRUE 1
#define FALSE 0

void assertCustom(int boolean, char * message){

    if(boolean == TRUE){

        printf("TEST PASSED: %s\n", message );
    }
    if(boolean == FALSE){

        printf("TEST FAILED: %s\n", message );
    }

}
//unit test 4 tests to check next player's turn
//this acts to check if another player is existant 
int main (int argc, char** argv)	{
    struct gameState G;
    int a;
	int k[10] = {adventurer, gardens, minion, village, embargo, mine, cutpurse, baron, tribute, smithy};
	
	printf ("\n** Unit Test 4: whosTurn() **\n");
	
	printf("\nRunning test 3 times because base game is set to 4 players\n");
	printf("Checking to see if other three players are still legal targets\n");
    for (int x = 2 ; x < 5 ; ++x)	{
    	printf("Testing game with %d player\n", x);
        a = initializeGame(x, k, 5, &G);
        a = whoseTurn(&G);
        assertCustom(a == G.whoseTurn, "for this number of players");		
	}

	printf("\n** End of Unit Test 4: whosTurn() **\n");

	return 0;
}