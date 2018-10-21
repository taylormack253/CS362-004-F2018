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
#define TESTFXN "isGameOver()"


void assertCustom(int boolean, char * passMsg, char * failMsg){

    if(boolean == TRUE){

        printf("TEST PASSED: %s\n", passMsg );
    }
    if(boolean == FALSE){

        printf("TEST FAILED: %s\n", failMsg );


    }
}

// Function to test that the game state was not altered by isGameOver
void gameTests(int player,struct gameState G, struct gameState testG){

    assertCustom(testG.handCount[player] == G.handCount[player], "Player 1 receives No cards");
    assertCustom(testG.handCount[player+1] == G.handCount[player+1], "Player 2 receives No cards");
    assertCustom(testG.deckCount[player] == G.deckCount[player], "Player 1 deck has the same number of cards");
    assertCustom(testG.deckCount[player+1] == G.deckCount[player+1], "Player 2 deck has the same number of cards");
    assertCustom(testG.coins == G.coins, "No extra coins received");
    assertCustom(testG.whoseTurn == G.whoseTurn, "Same Players Turn");
    assertCustom(testG.numActions == G.numActions, "Number of actions" );
    assertCustom(testG.numBuys == G.numBuys, "Number of Buys" );
    assertCustom(testG.playedCardCount == G.playedCardCount, "Number of Cards Discarded");
    assertCustom(testG.numPlayers == G.numPlayer, "Same number of players in the game")
    //assertGameState(player+1, &G, &testG);

}



int main() {

    int seed = 1000;
    int numPlayers = 2;
    int player = 0;
    //int bonus = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

   	printf("----------------- Unit test for function: %s ----------------\n", TESTFXN);
   
    //copy game state
    memcpy(&testG, &G, sizeof(struct gameState));


    // province pile empty
    testG.supplyCount[province] = NO_CARDS;

    //copy game state for both test games
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("Test no province cards left\n");
    // test that the game is over
    assertCustom(isGameOver(&testG) == TRUE, "Game over: No province Cards", "Game NOT over but not province cards left");
    gameTests(player, G, testG);

    // re-initilize the game struct
    memcpy(&testG, &G, sizeof(struct gameState));

    // Test 2 piles empty
    testG.supplyCount[curse] = NO_CARDS;
    testG.supplyCount[adventurer] = NO_CARDS;

    //copy game state for both test games
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("Test 2 piles with no cards left\n");
    assertCustom(isGameOver(&testG)== FALSE, "Game not over: Only 2 piles have no Cards", "Game over but only 2 empty supply piles");
    gameTests(player, G, testG);

    // Test 3 piles empty
    testG.supplyCount[gold] = NO_CARDS;
    printf("Test 3 piles with no cards left\n");

    //copy game state for both test games
    memcpy(&testG, &G, sizeof(struct gameState));

    assertCustom(isGameOver(&testG)== TRUE, "Game over: Curse, Adventurer, Gold have no Cards", "Game NOT over even though 3 supply piles are empty");
    gameTests(player, G, testG);

    // Test 3 piles empty and provinces
    testG.supplyCount[province] = NO_CARDS;
    printf("Test 3 piles with no cards left and no provinces\n");

    //copy game state for both test games
    memcpy(&testG, &G, sizeof(struct gameState));
    
    assertCustom(isGameOver(&testG)== TRUE, "Game over: Curse, Adventurer, Gold and Province no Cards", "Game NOT over even though 3 supply piles and provinces are empty");
    gameTests(player, G, testG);


	printf("----------------- End of unit test for: %s ----------------\n", TESTFXN);

    return 0;
}