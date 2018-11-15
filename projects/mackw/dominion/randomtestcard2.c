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
#define TESTCARD "Great Hall"
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


int main() {
   
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};


  //const int newCards = 1;
    //int discarded = 1;
  //const int xtraCoins = 0;
    //int shuffledCards = 0;
    //int numBuys = 0;
  //const int numActions = 1;
    int minimumHandSize = 5;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers;
    int player = 0;
    int i;
    int passedTestCount = 0, handCountFail = 0, deckCountFail = 0, coinCountFail =  0, whoseTurnFail = 0,
        numActionsFail = 0, numBuysFail = 0, playedCardFail = 0;


    srand((unsigned int)(time(NULL)));

    init_randomNumbers();

    for(i = 0; i < TESTRUNS; i++) {
        printf("----------------- Great Hall Test Number %d ----------------\n\n", i);
         numPlayers = randomInt(3) + 2;
         initializeGame(numPlayers, k, seed, &G);

         //add cards to deck, hand and discard vary number of players
         int positionToAddCard, testDeckSize;

         testDeckSize = randomInt(MAX_DECK) + 1;

        for (player = 0; player < numPlayers; player++) {

            if(testDeckSize > minimumHandSize){
                if(Random() < .95) {
                    G.handCount[player] = minimumHandSize;
                }
                else{
                    int bigHand =   (int) (minimumHandSize * 10 * Random());
                    G.handCount[player] = bigHand > testDeckSize ? testDeckSize : bigHand;
                }
            }

            else{
                G.handCount[player] = testDeckSize;
            }

            testDeckSize -= G.handCount[player];


            for (positionToAddCard = 0; positionToAddCard < G.handCount[player]; positionToAddCard++) {

                G.hand[player][positionToAddCard] = randomInt(NUM_CARDS);


            }

        }



        for (player = 0; player < numPlayers; player++) {

             G.deckCount[player] = randomInt(testDeckSize);
             testDeckSize -= G.deckCount[player];

             for (positionToAddCard = 0; positionToAddCard < G.deckCount[player]; positionToAddCard++) {

                 G.deck[player][positionToAddCard] = randomInt(NUM_CARDS);


             }
         }




         for (player = 0; player < numPlayers; player++) {

             G.discardCount[player] = testDeckSize;

             for (positionToAddCard = 0; positionToAddCard < G.discardCount[player]; positionToAddCard++) {

                 G.discard[player][positionToAddCard] = randomInt(NUM_CARDS);


             }
         }

        if(handpos < G.handCount[player]){
            G.hand[player][handpos] = great_hall;
        }
        else{
            G.hand[player][0] = great_hall;
        }


         memcpy(&testG, &G, sizeof(struct gameState));



         cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);


        // test player receives 1 card
        if(testG.handCount[player] != G.handCount[player]){
            printf("TEST FAILED: player does NOT receive 1 card\n\n");
            handCountFail++;
            passed = 0;
        }
        // test cards came from players deck
        if(testG.deckCount[player] != G.deckCount[player] - 1){
            printf("TEST FAILED: Card DID NOT come from player's deck or incorrect number of cards drawn\n\n");
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
    printf("# of num buys fails: %d\n", numBuysFail);
    printf("# of played card count fails: %d\n", playedCardFail);
    printf("# of successful tests: %d\n", passedTestCount);


    return 0;
}