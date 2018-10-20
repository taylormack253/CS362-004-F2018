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

void assertGameState(int player, struct gameState * oldG, struct gameState * newG){
    int failed = FALSE;
    if(oldG->handCount[player] !=   newG->handCount[player]){
        printf("TEST FAILED: Hand Count for non-action player Changed\n");
        failed = TRUE;
    }
    if(oldG->numPlayers != newG->numPlayers){
        printf("TEST FAILED: Number of Players in Game Changed\n");
        failed = TRUE;
    }
    if(oldG->deckCount[player] !=   newG->deckCount[player]){
        printf("TEST FAILED: Deck Count for non-action player Changed\n");
        failed = TRUE;
    }
    int i;
    for(i = curse; i < NUM_CARDS; i++){
        if(oldG->supplyCount[i] != newG->supplyCount[i]){
            printf("TEST FAILED Card %d Supply Count Changed\n", i);
           failed = TRUE;
        }
        if(oldG->embargoTokens[i] != newG->embargoTokens[i]){
            printf("TEST FAILED Embargo Token on Card %d Changed\n", i);
            failed = TRUE;

        }
    }
    if(!failed){
        printf("TEST PASSED: Game State Invariants\n");
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

    printf ("TESTING updateCoins():\n");
    // loop all players
    for (p = 0; p < numPlayer; p++)
    {
    	// loop each card in hand
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
        	// test each bonus amount
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
                printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                updateCoins(p, &G, bonus);


                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
                assert(G.coins == handCount * 1 + bonus); // check if the number of coins is correct

                memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
                updateCoins(p, &G, bonus);

                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
                assert(G.coins == handCount * 2 + bonus); // check if the number of coins is correct

                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                updateCoins(p, &G, bonus);

                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
                assert(G.coins == handCount * 3 + bonus); // check if the number of coins is correct
            }
        }
    }

    printf("All tests passed!\n");

    return 0;
}