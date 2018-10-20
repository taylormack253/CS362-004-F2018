///////////////////////////////////////////////////////////////////////
// File: unittest2.c
// Author: William Taylor Mack
// Description: Unit testing for ______________________

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "assertFxns.h"
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



int main() {
    int i;
    int seed = 100;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    
    // create test hands all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

	printf("\n** Unit Test 3: updateCoins() **\n");

    // loop all players
    for (p = 0; p < numPlayer; p++)
    {
    	// loop 5 times so hands contain 1 to 5 treasure cards.
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
        	// test each bonus amount
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
                printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
                // clear the game state
                memset(&G, 23, sizeof(struct gameState));   
                
                // set the number of cards in hand
                G.handCount[p] = handCount;                 
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
               
                printf ("Test all coppers in player hand\n");
                updateCoins(p, &G, bonus);
                assertCustom(G.coins == handCount * 1 + bonus, "number of coins is correct"); // check if the number of coins is correct

                // copy all silvers to players hand
                memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
                updateCoins(p, &G, bonus);

                printf ("Test all silvers in player hand\n");
                assertCustom(G.coins == handCount * 2 + bonus, "number of coins is correct"); // check if the number of coins is correct

                // copy all golds to players hand
                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                updateCoins(p, &G, bonus);

                printf ("Test all golds in player hand\n");
                assertCustom(G.coins == handCount * 3 + bonus, "number of coins is correct"); // check if the number of coins is correct
            }
        }
    }

	printf("\n** End of Unit Test 2: updateCoins() **\n");

    return 0;
}