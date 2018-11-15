// randomtestcard2.c
// By: William Taylor Mack
// CS362 Assignment-4

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
//#include "assertCustom.h"
#include <stdlib.h>
#include <tgmath.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define NUM_CARDS 27
#define TESTCARD "smithy"
#define TESTRUNS 10
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

void assertCustom(int boolean, int fail, char * passMsg, char * failMsg){

    if(boolean == TRUE){
        printf("TEST PASSED: %s\n", passMsg );
    }
    if(boolean == FALSE){
        printf("TEST FAILED: %s\n", failMsg );
        fail = 1;
    }
}

int main() {
    srand((unsigned int)(time(NULL)));


    int newCards = 0;
    int discarded = 1;
    //int xtraCoins = 0;
    //int shuffledCards = 0;
    //int numBuys = 0;
    //int numActions =0;
    //int minimumHandSize = 5;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 3;
    //int player = 0;
   
    int passedTestCount = 0, handCountFail = 0, deckCountFail = 0, coinCountFail =  0, whoseTurnFail = 0,
        numActionsFail = 0, numBuysFail = 0, playedCardFail = 0;
    
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards

    int i;

    init_randomNumbers();

    for(i = 0; i < TESTRUNS; i++) {
        printf("----------------- Smithy Test Number %d ----------------\n\n", i);
         numPlayers = randomInt(numPlayers) + 2;
         //numPlayers = rand() % 4 + 2;
         initializeGame(numPlayers, k, seed, &G);

         //add cards to deck, hand and discard vary number of players
         int player, positionToAddCard, testDeckSize, passed = 1;

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
            G.hand[player][handpos] = smithy;
        }
        else{
            G.hand[player][0] = smithy;
        }


         memcpy(&testG, &G, sizeof(struct gameState));


         newCards = 3;

         cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);




        // test player receives 3 cards
        if(testG.handCount[player] != G.handCount[player] + 3 - 1){
            printf("TEST FAILED: player does NOT recive 3 cards\n\n");
            handCountFail++;
            passed = 0;
        }
        // test cards came from players deck
        if(testG.deckCount[player] != G.deckCount[player] - 3){
            printf("TEST FAILED: Cards DID NOT come from player's deck or incorrect number of cards drawn\n\n");
            deckCountFail++;
            passed = 0;
        } 
        // test no extra coins given
        if(testG.coins != G.coins){
            printf("TEST FAILED: Extra coins recieved\n\n");
            coinCountFail++;
            passed = 0;
        } 
        // test same players turn
        if(testG.whoseTurn != G.whoseTurn){
            printf("TEST FAILED: NOT same players turn\n\n");
            whoseTurnFail++;
            passed = 0;
        } 
        // test number of actions is same
        if(testG.numActions != G.numActions){
            printf("TEST FAILED: Number of actions changed\n\n");
            numActionsFail++;
            passed = 0;
        } 
        // test number of buys is same
        if(testG.numBuys != G.numBuys){
            printf("TEST FAILED: Number of buys changed\n\n");
            numBuysFail++;
            passed = 0;
        } 
        // test played card count
        if(testG.playedCardCount != G.playedCardCount + 1){
            printf("TEST FAILED: Played card count incorrect\n\n");
            playedCardFail++;
            passed = 0;
        } 
        // all tests passed
        if (passed)
            passedTestCount++;
    }

    printf("# of hand count fails: %d\n", handCountFail);
    printf("# of deck count fails: %d\n", deckCountFail);
    printf("# of coin count fails: %d\n", coinCountFail);
    printf("# of whose turn fails: %d\n", whoseTurnFail);
    printf("# of num actions fails: %d\n", numActionsFail);
    printf("# of num actions fails: %d\n", numBuysFail);
    printf("# of played card count fails: %d\n", playedCardFail);
    printf("# of successful tests: %d\n", passedTestCount);

    return 0;
}