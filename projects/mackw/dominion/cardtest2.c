///////////////////////////////////////////////////////////////////////
// File: cardtest2.c
// Author: William Taylor Mack
// Description: Card testing for great hall.
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "great_hall"


void assertCustom(int boolean, char * message){

    if(boolean == TRUE){

        printf("TEST PASSED: %s\n", message );
    }
    if(boolean == FALSE){

        printf("TEST FAILED: %s\n", message );


    }

}


int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int numBuys = 0;
    int numActions = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    //Great Hall should receive one card and one action
    //copy game state
    memcpy(&testG, &G, sizeof(struct gameState));

    cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);
    newCards = 1;
    xtraCoins = 0;
    numActions = 1;


    assertCustom(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "Receives 1 cards");
    assertCustom(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, "Deck has 1 less Cards");
    assertCustom(testG.coins == G.coins + xtraCoins, "No extra coins received");
    assertCustom(testG.whoseTurn == G.whoseTurn, "Same Player's Turn");
    assertCustom(testG.numActions == G.numActions + numActions, "Number of actions" );
    assertCustom(testG.numBuys == G.numBuys + numBuys, "Number of Buys" );
    assertCustom(testG.playedCardCount == G.playedCardCount + discarded, "Number of Cards Discarded");
    //assertGameState(thisPlayer+1, &G, &testG);



    return 0;
}

