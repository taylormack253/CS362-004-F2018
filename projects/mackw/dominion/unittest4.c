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
#define TESTFXN "whosTurn()"

void assertCustom(int boolean, char * passMsg, char * failMsg){

    if(boolean == TRUE){

        printf("TEST PASSED: %s\n", passMsg );
    }
    if(boolean == FALSE){

        printf("TEST FAILED: %s\n", failMsg );


    }
}

//unit test 4 tests to check next player's turn
//this acts to check if another player is existant 
int main (int argc, char** argv){
    struct gameState G;
    int a;
	int k[10] = {adventurer, gardens, minion, village, embargo, mine, cutpurse, baron, tribute, smithy};
	
	printf("----------------- Unit test for function: %s ----------------\n", TESTFXN);
	
    for (int x = 2 ; x < 5 ; x++){
    	printf("Testing game with %d players\n", x);
        a = initializeGame(x, k, 5, &G);
        a = whoseTurn(&G);
        assertCustom(a == G.whoseTurn, "CORRECT players turn", "INCORRECT players turn");		
	}

    printf("----------------- End of unit test for: %s ----------------\n", TESTFXN);

	return 0;
}