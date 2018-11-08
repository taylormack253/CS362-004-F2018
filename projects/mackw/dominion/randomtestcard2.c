// randomtestcard2.c
// By: William Taylor Mack
// CS362 Assignment-4

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "assertCustom.h"
#include <stdlib.h>
#include <tgmath.h>
#include <time.h>
#define TESTCARD "smithy"
#define TESTRUNS 80
#define TESTRUNS_SIZE (TESTRUNS * MAX_DECK * MAX_PLAYERS * 10)
#define DEBUG 0

static double randomNumbers[TESTRUNS * MAX_DECK * MAX_PLAYERS * 10];
static int positionInRandomNumbers = 0;

void init_randomNumbers(){
    int i;
    for(i = 0; i < TESTRUNS_SIZE; i++){

    randomNumbers[i] = Random();

    }

}

int randomInt(int intMax){
  // int random = (int) (Random() * intMax);
   int random = (int)(intMax * randomNumbers[positionInRandomNumbers++]);
    if(DEBUG){printf("Random Number: %d\t", random);}
    return random;
}


int main() {
    srand((unsigned int)(time(NULL)));


    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int numBuys = 0;
    int numActions =0;
    int minimumHandSize = 5;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 3;
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards

    int i;

    init_randomNumbers();

    for(i = 0; i < TESTRUNS; i++) {
        printf("----------------- Test Number %d, Card: %s (ONLY FAILURES PRINTED)----------------\n", i,  TESTCARD);
         numPlayers = randomInt(numPlayers) + 2;
         initializeGame(numPlayers, k, seed, &G);

         //add cards to deck, hand and discard vary number of players
         int player, positionToAddCard, testDeckSize;

         testDeckSize = randomInt(MAX_DECK);

         for (player = 0; player < numPlayers; player++) {

             G.deckCount[player] = randomInt(testDeckSize);
             testDeckSize -= G.deckCount[player];

             for (positionToAddCard = 0; positionToAddCard < G.deckCount[player]; positionToAddCard++) {

                 G.deck[player][positionToAddCard] = randomInt(NUM_CARDS);


             }
         }


         for (player = 0; player < numPlayers; player++) {

             G.handCount[player] = randomInt(testDeckSize);
             testDeckSize -= G.handCount[player];


             for (positionToAddCard = 0; positionToAddCard < G.handCount[player]; positionToAddCard++) {

                 G.hand[player][positionToAddCard] = randomInt(NUM_CARDS);


             }

         }


         for (player = 0; player < numPlayers; player++) {

             G.discardCount[player] = testDeckSize;

             for (positionToAddCard = 0; positionToAddCard < G.discardCount[player]; positionToAddCard++) {

                 G.discard[player][positionToAddCard] = randomInt(NUM_CARDS);


             }
         }

        if(handpos < G.handCount[player]){
            G.hand[thisPlayer][handpos] = smithy;
        }
        else{
            G.hand[thisPlayer][0] = smithy;
        }


         memcpy(&testG, &G, sizeof(struct gameState));


         newCards = 3;
         xtraCoins = 0;
         shuffledCards = 0;
         if (testG.deckCount[thisPlayer] <= newCards) {

             shuffledCards = testG.discardCount[thisPlayer];

         }


         cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);


         assertCustom(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "Receives 3 cards", &G,
                      &testG);
         assertCustom(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards,
                      "Deck has 3 less Cards", &G, &testG);
         assertCustom(testG.coins == G.coins + xtraCoins, "No extra coins received", &G, &testG);
         assertCustom(testG.whoseTurn == G.whoseTurn, "Same Players Turn", &G, &testG);
         assertCustom(testG.numActions == G.numActions, "Number of actions", &G, &testG);
         assertCustom(testG.numBuys == G.numBuys, "Number of Buys", &G, &testG);
         assertCustom(testG.playedCardCount == G.playedCardCount + discarded, "Number of Cards Discarded", &G, &testG);
         assertGameState(thisPlayer + 1, &G, &testG);

    }

    return 0;
}