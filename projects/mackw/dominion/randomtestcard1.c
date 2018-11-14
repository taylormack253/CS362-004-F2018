// randomtestcard1.c
// By: William Taylor Mack
// CS362 Assignment-4

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>


int main(int argc, char** argv) {
    struct gameState G;
    //int seed = 1000;
    int numPlayers = 2;
    int player = 0;
    int k[10] = {adventurer, great_hall, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room}; 
    int deckSize;
    int handSize;
    int handPos;
    int deckBefore;
    int deckAfter;
    int handBefore;
    int handAfter;
    int discardBefore;
    int discardAfter;
    int i;
    int deckFailure = 0;
    int handFailure = 0;
    int discardFailure = 0;
    int testPassed = 0;
    int passed;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    
    srand(time(NULL));
 
    for(i = 0; i < 10; i++){
        //set random number of players
        numPlayers = randomInt(numPlayers) + 2;

        initializeGame(numPlayers, k, atoi(argv[1]), &G);

        // set random deck size
        deckSize = rand() % (MAX_DECK + 1);
        
        // set random handsize
        handSize = rand() % (deckSize + 1);
      


        
        G.deckCount[0] = deckSize - handSize;
        G.handCount[0] = handSize;

        handPos = G.hand[player][G.handCount[player] - 1];
        //personal checks
        deckBefore = G.deckCount[0];
        //printf("deck before %d\n", deckBefore);
        handBefore = G.handCount[0];
        //printf("Hand before %d\n",handBefore);
        discardBefore = G.playedCardCount;
        //printf("Discard before %d\n", discardBefore);
        
        
        //smithyEffect(handPos, player, &G);
        cardEffect(smithy, choice1, choice2, choice3, &G, handPos, &bonus);
        
        deckAfter = G.deckCount[0];
        //printf("deck after %d\n", deckAfter);
        handAfter = G.handCount[0];
        //printf("hand After %d\n", handAfter);
        discardAfter = G.playedCardCount;
        //printf("Discard After %d\n\n", discardAfter);
        
        passed = 1;
        
        // test 2 cards are drawn
        if(handAfter != (handBefore + 2)){
            printf("Incorrect amount of cards drawn: Test Failed\n\n");
            handFailure++;
            passed = 0;
        }
        
        // test 3 cards are removed from the deck
        if(deckAfter != (deckBefore - 3)){
            printf("Incorrect number of cards removed from deck: Test Failed\n\n");
            deckFailure++;
            passed = 0;
        }
        
        // test 1 card was discarded
        if(discardAfter != (discardBefore + 1)){
            printf("Smithy Not Discarded after use: Test Failed\n\n");
            discardFailure++;
            passed = 0;
        }
        
        // all tests passed
        if(passed == 1){
            printf("All Tests Passed!!\n\n");
            testPassed++;
        }
        
    }
        
    // Print test results
   printf("\n\n");
   printf("# of Tests Passed: %d\n", testPassed);
   printf("# of Cards Drawn To Hand Failed: %d\n", handFailure);
   printf("# of Smithy Discarded Fails: %d\n\n", discardFailure);        
   
   return 0;
}