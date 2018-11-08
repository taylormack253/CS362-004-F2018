// randomtestadventurer.c
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
#define TESTCARD "Adventurer"
#define TESTRUNS 100
#define TESTRUNS_SIZE (TESTRUNS * MAX_DECK * MAX_PLAYERS * 100)
#define DEBUG 0

struct drawnTreasurerByAdventure{
  int type;
  int location;
};


static double randomNumbers[TESTRUNS * MAX_DECK * MAX_PLAYERS * 100];
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
    if(DEBUG){printf("Random Number: %d\t\n", random);}
    return random;
}


int main() {
    srand((unsigned int)(time(NULL)));



  const int newCards = 2;
    int discarded = 0;
  const int xtraCoins = 0;
    int shuffledCards = 0;
    int numBuys = 0;
  const int numActions =0;
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
        printf("----------------- Test Number %d, Card: %s (ONLY FAILURES PRINTED)----------------\n", i, TESTCARD);


        numPlayers = randomInt(numPlayers) + 2;
        initializeGame(numPlayers, k, seed, &G);


        //add cards to deck, hand and discard vary number of players
        int player, positionToAddCard, testDeckSize;

        testDeckSize = randomInt(MAX_DECK) + 1;

        for (player = 0; player < numPlayers; player++) {

            if (testDeckSize > minimumHandSize) {
                if (Random() < .95) {
                    G.handCount[player] = minimumHandSize;
                }/** else {
                    int bigHand = (int) (minimumHandSize * 10 * Random());
                    G.handCount[player] = bigHand > testDeckSize ? testDeckSize : bigHand;
                } **/
            } else {
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

        if (handpos < G.handCount[player]) {
            G.hand[thisPlayer][handpos] = adventurer;
        } else {
            G.hand[thisPlayer][0] = adventurer;
        }


        memcpy(&testG, &G, sizeof(struct gameState));


        shuffledCards = 0;

        int drawnCards = 0;
        int treasureCount = 0;
        int end;

        struct drawnTreasurerByAdventure treasure[2];
        while (drawnCards < (G.deckCount[thisPlayer]) && treasureCount < 2) {

            for (end = G.deckCount[thisPlayer] - 1; end > -1; end--) {
                drawnCards++;
                if (G.deck[thisPlayer][end] == gold || G.deck[thisPlayer][end] == silver ||
                    G.deck[thisPlayer][end] == copper) {
                    treasure[treasureCount].type = G.deck[thisPlayer][end];
                    treasure[treasureCount].location = drawnCards;
                    treasureCount++;
                }
                if (treasureCount == 2) { break; }

            }


        }
        while (drawnCards < (G.deckCount[thisPlayer] + G.discardCount[thisPlayer]) && treasureCount < 2) {

            for (end = G.discardCount[thisPlayer] - 1; end > -1; end--) {
                drawnCards++;
                if (G.discard[thisPlayer][end] == gold || G.discard[thisPlayer][end] == silver ||
                    G.discard[thisPlayer][end] == copper) {
                    treasure[treasureCount].type = G.discard[thisPlayer][end];
                    treasure[treasureCount].location = drawnCards;
                    treasureCount++;
                }
                if (treasureCount == 2) { break; }

            }


        }




        if (G.deckCount[thisPlayer] < drawnCards) {

            shuffledCards = G.discardCount[thisPlayer];

        }

        if (drawnCards == (G.deckCount[thisPlayer] + G.discardCount[thisPlayer])) {

            printf("Warning Possible Infinite Loop\n");
        }




            cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);


        int handCount = testG.handCount[thisPlayer];
            assertCustom(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded,
                         "Receives 2 cards", &G,
                         &testG);
            assertCustom(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - drawnCards + shuffledCards,
                         "Deck Less Card", &G, &testG);

            if(DEBUG){printf("First Treasure %d ", treasure[0].type);}
            if(DEBUG){printf("Second Treasure %d ", treasure[1].type);}
        if(DEBUG){printf("Actual First Treasure %d\n ", testG.hand[thisPlayer][handCount - 1]);}
        if(DEBUG){printf("Actual Second Treasure %d\n ", testG.hand[thisPlayer][handCount - 2]);}
            assertCustom(testG.hand[thisPlayer][handCount - 1] == treasure[1].type, "First Treasure", &G, &testG);
            assertCustom(testG.hand[thisPlayer][handCount - 2] == treasure[0].type, "Second Treasure", &G, &testG);

            if (shuffledCards) {
                assertCustom(testG.discardCount[thisPlayer] == 0,
                             "Discard Pile has shuffle", &G, &testG);
            } else {

                assertCustom(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + drawnCards - newCards, "Discard", &G, &testG);
            }

            assertCustom(testG.playedCardCount = G.playedCardCount + drawnCards, "Played Card Count", &G, &testG);
            assertCustom(testG.coins == G.coins + xtraCoins, "No extra coins received", &G, &testG);
            assertCustom(testG.whoseTurn == G.whoseTurn, "Same Players Turn", &G, &testG);
            assertCustom(testG.numActions == G.numActions + numActions, "Number of actions", &G, &testG);
            assertCustom(testG.numBuys == G.numBuys, "Number of Buys", &G, &testG);

            assertGameState(thisPlayer + 1, &G, &testG);



    }

    return 0;
}