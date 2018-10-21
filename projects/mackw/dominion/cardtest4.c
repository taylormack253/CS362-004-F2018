///////////////////////////////////////////////////////////////////////
// File: cardtest4.c
// Author: William Taylor Mack
// Description: Card testing for adventurer
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"
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
    int handCount = testG.handCount[player];
    int i;
    assertCustom(testG.handCount[player] == G.handCount[player] + 1, "Player 1 receives 2 cards", "Incorrect number of cards drawn");
    assertCustom(testG.deckCount[player] == G.deckCount[player] - 2, "Cards came from Player 1's deck", "Cards DID NOT come from Player 1's deck or incorrect number of cards drawn");
    assertCustom(testG.handCount[player+1] == G.handCount[player+1], "Player 2 receives no cards", "Player 2 hand count changed");
    assertCustom(testG.deckCount[player+1] == G.deckCount[player+1], "Player 2 deck has same number of cards", "Player 2 deck count chnaged");
    assertCustom(testG.coins == G.coins, "No extra coins received","Extra coins recieved");
    assertCustom(testG.whoseTurn == G.whoseTurn, "Same Players Turn", "NOT same players turn");
    assertCustom(testG.numActions == G.numActions, "Number of actions correct", "Number of actions incorrect" );
    assertCustom(testG.numBuys == G.numBuys, "Number of buys same", "Number of buys changed" );
    assertCustom(testG.playedCardCount == G.playedCardCount + 1, "1 card played", "Played card count incorrect");
    assertCustom(testG.numPlayers == G.numPlayers, "Same number of players in the game", "Number of players in game changed");

    if(testG.hand[player][handCount-1] == copper || testG.hand[player][handCount-1] == silver || testG.hand[player][handCount-1] == gold){
        printf("TEST PASSED: 1st card kept was a treasure card\n");
    }
    else{
        printf("TEST FAILED: 1st card kept was not treasure card\n");
    }


    if(testG.hand[player][handCount-2] == copper || testG.hand[player][handCount-2] == silver || testG.hand[player][handCount-2] == gold){
        printf("TEST PASSED: 2nd card kept was a treasure card\n");
    }
    else{
        printf("TEST FAILED: 2nd card kept was not treasure card\n");
    }


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
    //int newCards = 0;
    //int discarded = 1;
    //int xtraCoins = 0;
    //int shuffledCards = 0;
    //int numBuys = 0;
    //int numActions = 0;
    //int handCount;
    //int deckcount;
    //int newDeckCount;
    //int i;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    //int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int player = 0;
    //int nextPlayer = 1;
    struct gameState G, testG;
    int k[10] = {adventurer, great_hall, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    

    printf("----------------- Testing Card State: %s ----------------\n", TESTCARD);
   
    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    //copy game state
    memcpy(&testG, &G, sizeof(struct gameState));
    
    // play card
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
   
    // adventureer will draw cards untill 2 treasures drawn.
    gameTests(player, G, testG);

    printf("--------------- Create new game and test again  -------------\n");

    seed = 5;
    // initilize new game with new seed
    initializeGame(numPlayers, k, seed, &G);

    //copy game state
    memcpy(&testG, &G, sizeof(struct gameState));
    
    // play card
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
   
    // adventureer will draw cards until 2 treasures drawn.
    gameTests(player, G, testG);


    return 0;
}