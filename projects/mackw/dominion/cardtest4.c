///////////////////////////////////////////////////////////////////////
// File: cardtest4.c
// Author: William Taylor Mack
// Description: Card testing for ______________________

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

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
    int handCount;
    int deckcount;
    int  newDeckCount;
    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int nextPlayer = 1;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    printf("----------------- Testing Card State: %s ----------------\n", TESTCARD);
   
    //copy game state
    printf("--------------------Test Case Copper, Copper, Gold ------------");
    memcpy(&testG, &G, sizeof(struct gameState));

    deckcount = testG.deckCount[thisPlayer];


    int newDeck1 [] = {copper, copper, gold};
    newDeckCount = 3;

    for(i = 0; i < newDeckCount; i++){
        testG.deck[thisPlayer][--deckcount] = newDeck1[i];
    }



    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    newCards = 2;
    xtraCoins = 0;
    numBuys = 0;
    handCount = testG.handCount[thisPlayer];


    assertCustom(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "Receives 2 cards");
    assertCustom(testG.hand[thisPlayer][--handCount] == copper, "First Treasure is Copper");
    assertCustom(testG.hand[thisPlayer][--handCount] == copper, "Second Treasure is Copper");
    assertCustom(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, "Deck has 2 less Cards");
    assertCustom(testG.coins == G.coins + xtraCoins, "No extra coins received");
    assertCustom(testG.whoseTurn == G.whoseTurn, "Same Player's Turn");
    assertCustom(testG.numActions == G.numActions, "Number of actions" );
    assertCustom(testG.numBuys == G.numBuys + numBuys, "Number of Buys" );
    assertCustom(testG.playedCardCount == G.playedCardCount + discarded, "Number of Cards Discarded");

    //assertGameState(nextPlayer, &G, &testG);



    memcpy(&testG, &G, sizeof(struct gameState));

    deckcount = testG.deckCount[thisPlayer];


    printf("--------------------Test Case Gold, Province, Silver ------------");
    int newDeck2 [] = {silver, province, gold};
    newDeckCount = 3;

    for(i = 0; i < newDeckCount; i++){
        testG.deck[thisPlayer][--deckcount] = newDeck2[i];
    }

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    newCards = 2;
    xtraCoins = 0;
    numActions = 0;
    numBuys = 0;
    handCount = testG.handCount[thisPlayer];
    discarded = 1;

    assertCustom(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "Receives 2 cards");
    assertCustom(testG.hand[thisPlayer][--handCount] == gold, "First Treasure is Gold");
    assertCustom(testG.hand[thisPlayer][--handCount] == silver, "Second Treasure is Silver");
    assertCustom(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards - 1 + shuffledCards, "Deck has 3 less Cards");
    assertCustom(testG.coins == G.coins + xtraCoins, "No extra coins received");
    assertCustom(testG.whoseTurn == G.whoseTurn, "Same Player's Turn");
    assertCustom(testG.numActions == G.numActions, "Number of actions" );
    assertCustom(testG.numBuys == G.numBuys + numBuys, "Number of Buys" );
    assertCustom(testG.playedCardCount == G.playedCardCount + discarded+1, "Number of Cards Discarded");




    //assertGameState(nextPlayer, &G, &testG);




    return 0;
}