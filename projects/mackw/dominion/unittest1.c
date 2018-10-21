///////////////////////////////////////////////////////////////////////
// File: unittest1.c
// Author: William Taylor Mack
// Description: Unit testing for getCost function.

#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#define NO_CARDS 0
#define NUM_CARDS 27
#define TRUE 1
#define FALSE 0
#define TESTFXN "getCost()"

void assertCustom(int boolean, char * passMsg, char * failMsg){

    if(boolean == TRUE){

        printf("TEST PASSED: %s\n", passMsg );
    }
    if(boolean == FALSE){

        printf("TEST FAILED: %s\n", failMsg );


    }
}

int main () {
	// create card and initilize to 0
	int card = 0;
	int cost = 0;
	int i = 0;
	int cardCosts[] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4,-1};


	printf("----------------- Testing function: %s ----------------\n", TESTFXN);

	// print cards and costs
	while (i <= NUM_CARDS){
		if (i == NUM_CARDS){
			printf("Test invalid card id\n");
			cost = getCost(card);
			assertCustom(cost == cardCosts[i], "Returned value of -1", "Cost of invalid card id INCORRECT");
		}
		else{
			printf("Card #%d\n", card);
			cost = getCost(card);
			assertCustom(cost == cardCosts[i], "Cost of card CORRECT", "Cost of card INCORRECT");
		}
		// move to next card
		card++;
		i++;
	}

	printf("----------------- End of unit test for: %s ----------------\n", TESTFXN);

}
