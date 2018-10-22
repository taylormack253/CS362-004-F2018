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
#define NUM_CARDS 27

void assertCustom(int boolean, char * passMsg, char * failMsg){

    if(boolean == TRUE){

        printf("TEST PASSED: %s\n", passMsg );
    }
    if(boolean == FALSE){

        printf("TEST FAILED: %s\n", failMsg );


    }

}

void gameTests(int player,struct gameState G, struct gameState testG){
    int failed = FALSE;
    int i;
    assertCustom(testG.handCount[player] == G.handCount[player] + 3, "Player 1 receives 4 cards", "Incorrect number of cards drawn");
    assertCustom(testG.deckCount[player] == G.deckCount[player] - 4, "Cards came from Player 1's deck", "Cards DID NOT come from Player 1's deck or incorrect number of cards drawn");
    assertCustom(testG.handCount[player+1] == G.handCount[player+1] + 1, "Player 2 receives 1 card", "Player 2 hand count incorrect");
    assertCustom(testG.deckCount[player+1] == G.deckCount[player+1] - 1, "Card came from Player 2's deck", "Cards DID NOT come from Player 1's deck or incorrect number of cards drawn");
    assertCustom(testG.coins == G.coins, "No extra coins received","Extra coins recieved");
    assertCustom(testG.whoseTurn == G.whoseTurn, "Same Players Turn", "NOT same players turn");
    assertCustom(testG.numActions == G.numActions, "Number of actions correct", "Number of actions incorrect" );
    assertCustom(testG.numBuys == G.numBuys + 1, "Number of buys increased by 1", "Number of buys incorrect" );
    assertCustom(testG.playedCardCount == G.playedCardCount + 1, "1 card played", "Played card count incorrect");
    assertCustom(testG.numPlayers == G.numPlayers, "Same number of players in the game", "Number of players in game changed");

    for(i = curse; i < NUM_CARDS; i++){
        if(testG.supplyCount[i] != G.supplyCount[i]){
            printf("TEST FAILED Card %d Supply Count Changed\n", i);
           failed = TRUE;
        }
        if(testG.embargoTokens[i] != G.embargoTokens[i]){
            printf("TEST FAILED Embargo Token on Card %d Changed\n", i);
            failed = TRUE;
        }
    }
    if(!failed){
        printf("TEST PASSED: Supply count and embargo tokens same\n");
    }


}

int main() {
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int player = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, great_hall, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
                 
    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    printf("----------------- Testing Card: %s -------------------\n", TESTCARD);
       
    //copy game state
    memcpy(&testG, &G, sizeof(struct gameState));

    //play card
    cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

    //Council Room Player draws 4 cards and gets one buy, each other player draws a card.
    gameTests(player, G, testG);

    printf("----------------- End of card test for: %s ----------------\n\n\n", TESTCARD);
    
    return 0;
}
