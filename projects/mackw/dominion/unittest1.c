///////////////////////////////////////////////////////////////////////
// File: unittest1.c
// Author: William Taylor Mack
// Description: Unit testing for getCost function.

#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "rngs.h"

int cardCosts[] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};

int main () {
	// create card and initilize to 0
	int card; 
	card = 0;
	int cost; 
	cost = 0;
	int i;
	i = 0;

	printf ("Unit test 1\n");

	// print cards and costs
	while (i < 27){
		printf("Card #%d\n", card);
		cost = getCost(card);
		printf("Cost %d coins\n", cost);
		if (cost = cardCosts[i])
			printf("Cost is CORRECT\n");
		else 
			printf("Cost is INCORRECT\n");
		i++;
	}
	
}
