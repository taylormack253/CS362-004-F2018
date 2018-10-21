///////////////////////////////////////////////////////////////////////
// File: cardtest1.c
// Author: William Taylor Mack
// Description: Card testing for smithy.

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"
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

void gameTests(int player,struct gameState G, struct gameState testG){
    int failed = FALSE;
    int i;
    assertCustom(testG.handCount[player] == G.handCount[player] + 3 - 1, "Player 1 receives 3 cards");
    assertCustom(testG.deckCount[player] == G.deckCount[player] - 3, "Cards came from Player 1's deck");
    assertCustom(testG.handCount[player+1] == G.handCount[player+1], "Player 2 receives no cards");
    assertCustom(testG.deckCount[player+1] == G.deckCount[player+1], "Player 2 deck has same number of cards");
    assertCustom(testG.coins == G.coins, "No extra coins received");
    assertCustom(testG.whoseTurn == G.whoseTurn, "Same Players Turn");
    assertCustom(testG.numActions == G.numActions, "Number of actions" );
    assertCustom(testG.numBuys == G.numBuys, "Number of Buys" );
    assertCustom(testG.playedCardCount == G.playedCardCount, "Number of Cards Discarded");
    assertCustom(testG.numPlayers == G.numPlayer, "Same number of players in the game");

    for(i = curse; i < NUM_CARDS; i++){
        if(testG.supplyCount[i] != G.supplyCount[i]){
            printf("TEST FAILED Card %d Supply Count Changed\n", i);
           failed = TRUE;
        }
        if(oldG->embargoTokens[i] != newG->embargoTokens[i]){
            printf("TEST FAILED Embargo Token on Card %d Changed\n", i);
            failed = TRUE;

        }
    }
    if(!failed){
        printf("TEST PASSED: Supply count and embargo tokens same\n");
    }


}

int main() {
    //int newCards = 0;
    //int discarded = 1;
    //int xtraCoins = 0;
    int shuffledCards = 0;
    //int numBuys = 0;
    //int numActions =0;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int player = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    
    //copy game state
    memcpy(&testG, &G, sizeof(struct gameState));

    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    //newCards = 3;
    //xtraCoins = 0;

    //Smithy should receive exactly 3-cards
    gameTests(player, G, testG);

    /*
    assertCustom(testG.handCount[player] == G.handCount[player] + newCards - discarded, "Player 1 receives 3 cards");
    assertCustom(testG.deckCount[player] == G.deckCount[player] - newCards + shuffledCards, "Player 1 deck has 3 less cards");
    assertCustom(testG.handCount[player+1] == G.handCount[player+1], "Player 2 receives no cards");
    assertCustom(testG.deckCount[player+1] == G.deckCount[player+1], "Player 2 deck has same number of cards");
    assertCustom(testG.coins == G.coins + xtraCoins, "No extra coins received");
    assertCustom(testG.whoseTurn == G.whoseTurn, "Same Players Turn");
    assertCustom(testG.numActions == G.numActions, "Number of actions" );
    assertCustom(testG.numBuys == G.numBuys, "Number of Buys" );
    assertCustom(testG.playedCardCount == G.playedCardCount + discarded, "Number of Cards Discarded");
    //assertGameState(player+1, &G, &testG);
	*/


    return 0;
}