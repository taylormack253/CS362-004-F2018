///////////////////////////////////////////////////////////////////////
// File: unittest3.c
// Author: William Taylor Mack
// Description: Unit testing for isGameOver

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

// Function to test that the game state was not altered by isGameOver
void gameTests(int thisPlayer,struct gameState G, struct gameState testG){

    assertCustom(testG.handCount[thisPlayer] == G.handCount[thisPlayer], "Receives No cards");
    assertCustom(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], "Deck has the same number of cards");
    assertCustom(testG.coins == G.coins, "No extra coins received");
    assertCustom(testG.whoseTurn == G.whoseTurn, "Same Players Turn");
    assertCustom(testG.numActions == G.numActions, "Number of actions" );
    assertCustom(testG.numBuys == G.numBuys, "Number of Buys" );
    assertCustom(testG.playedCardCount == G.playedCardCount, "Number of Cards Discarded");
    assertGameState(thisPlayer+1, &G, &testG);

}



int main() {

    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int bonus = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

   printf ("\n** Unit Test 3: isGameOver() **\n");
   
    //copy game state
    memcpy(&testG, &G, sizeof(struct gameState));


    // province pile empty
    testG.supplyCount[province] = NO_CARDS;
    // test that the game is over
    assertCustom(isGameOver(&testG) == TRUE, "Game over: No province Cards");
    gameTests(thisPlayer, G, testG);

    // re-initilize the game struct
    memcpy(&testG, &G, sizeof(struct gameState));

    // Test 2 piles empty
    testG.supplyCount[curse] = NO_CARDS;
    testG.supplyCount[adventurer] = NO_CARDS;
    assertCustom(isGameOver(&testG)== FALSE, "Game over: Curse and Adventurer have no Cards");
    gameTests(thisPlayer, G, testG);

    // Test 3 piles empty
    testG.supplyCount[gold] = NO_CARDS;
    assertCustom(isGameOver(&testG)== TRUE, "Game over: Curse, Adventurer, Gold have no Cards");
    gameTests(thisPlayer, G, testG);

    // Test 3 piles empty and provinces
    testG.supplyCount[province] = NO_CARDS;
    assertCustom(isGameOver(&testG)== TRUE, "Game over: Curse, Adventurer, Gold and Province no Cards");
    gameTests(thisPlayer, G, testG);


	printf("\n** End of Unit Test 3: isGameOver() **\n");
    return 0;
}