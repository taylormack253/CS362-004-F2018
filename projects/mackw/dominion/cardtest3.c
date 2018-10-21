///////////////////////////////////////////////////////////////////////
// File: cardtest3.c
// Author: William Taylor Mack
// Description: Card testing for council room.

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council_room"
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
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int numBuys = 0;
    //int numActions = 0;

    //int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    //int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int nextPlayer = 1;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    //Council Room - each other player draws a card. Player draws 4 cards and gets one buy.
    //copy game state
    memcpy(&testG, &G, sizeof(struct gameState));

    cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
    newCards = 4;
    xtraCoins = 0;
    numBuys = 1;

    assertCustom(testG.handCount[thisPlayer] == G.handCount[thisPlayer] +newCards - discarded, "Receives 4 cards");
    assertCustom(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, "Deck has 4 less Cards");
    assertCustom(testG.coins == G.coins + xtraCoins, "No extra coins received");
    assertCustom(testG.whoseTurn == G.whoseTurn, "Same Player's Turn");
    assertCustom(testG.numActions == G.numActions, "Number of actions" );
    assertCustom(testG.numBuys == G.numBuys + numBuys, "Number of Buys" );
    assertCustom(testG.playedCardCount == G.playedCardCount + discarded, "Number of Cards Discarded");
    //each player draws a card need to decrement to assert GameState. As gamestate assumes no changes to other players

    testG.handCount[nextPlayer]--;

    //assertGameState(nextPlayer, &G, &testG);



    return 0;
}
