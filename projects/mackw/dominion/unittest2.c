///////////////////////////////////////////////////////////////////////
// File: unittest2.c
// Author: William Taylor Mack
// Description: Unit testing for updateCoins()
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define NO_CARDS 0
#define NUM_CARDS 27
#define TRUE 1
#define FALSE 0
#define TESTFXN "updateCoins()"

void assertCustom(int boolean, char * passMsg, char * failMsg){

    if(boolean == TRUE){

        printf("TEST PASSED: %s\n", passMsg );
    }
    if(boolean == FALSE){

        printf("TEST FAILED: %s\n", failMsg );


    }
}


int main() {
    int i;
    int seed = 100;
    int numPlayers = 2;
    int maxBonus = 10;
    int p, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
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

    // create game state
    initializeGame(numPlayers, k, seed, &G); // initialize a new game

	printf("----------------- Unit testing for function: %s ----------------\n", TESTFXN);

    // loop all players
    for (p = 0; p < numPlayers; p++)
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

                // coppy all coppers to players hand                 
                memcpy(G.hand[p], coppers, sizeof(int) * handCount);
               
                // printf ("Test all coppers in player hand\n");
                updateCoins(p, &G, bonus);

                // test coins
                assertCustom(G.coins == handCount * 1 + bonus, "Coin count with all copper tresasure cards in hand CORRECT", "Coin count with all copper tresure cards in hand INCORRECT"); // check if the number of coins is correct

                // copy all silvers to players hand
                memcpy(G.hand[p], silvers, sizeof(int) * handCount);
                updateCoins(p, &G, bonus);

                // Test coins
                assertCustom(G.coins == handCount * 2 + bonus, "Coin count with all silver tresasure cards in hand CORRECT", "Coin count with all silver tresasure cards in hand INCORRECT"); // check if the number of coins is correct

                // copy all golds to players hand
                memcpy(G.hand[p], golds, sizeof(int) * handCount); 
                updateCoins(p, &G, bonus);

                // test coins
                assertCustom(G.coins == handCount * 3 + bonus, "Coin count with all gold tresasure cards in hand CORRECT", "Coin count with all gold tresasure cards in hand INCORRECT"); // check if the number of coins is correct
            }
        }
    }

    printf("----------------- End of unit test for: %s ----------------\n\n\n", TESTFXN);

    return 0;
}