// randomtestadventurer.c
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
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};  
    int deckSize;
    int handSize;
    int i;
    int j;
    int q;
    int randomCard;
    int randK;
    int m;
    int coinCount;
    int x;
    int discardCopper;
    int discardSilver;
    int discardGold;
    int coinCountBefore;
    int testPassed = 0;
    int drawTestFailed = 0;
    int discardTestFailed = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    
    srand(time(NULL));
   //randomize hand size
    for(i = 0; i < 10; i++){
        initializeGame(numPlayers, k, atoi(argv[1]), &G);
        coinCountBefore = 0;
        // set random decksize
        deckSize = rand() % (MAX_DECK + 1);
        //set random handsize
        handSize = rand() % (deckSize + 1);
      
        
        G.deckCount[0] = deckSize - handSize;
        G.handCount[0] = handSize;
        
       
        
        for (j = 0; j < numPlayers; j++){
            for(q = 0;q < G.deckCount[j]; q++){
                randomCard = rand() % (50 + 1);
                randK = rand() % (10);
                if(randomCard == 1){
                    G.deck[j][q] = copper;
                } else if(randomCard == 2){
                    G.deck[j][q] = silver;
                }else if(randomCard == 3){
                    G.deck[j][q] = gold;
                }else {
                    G.deck[j][q] = k[randK];
                }
            }
        } 
        
        for(m = 0; m < G.handCount[player]; m++){
            if(G.hand[player][m] == copper || G.hand[player][m] == silver || G.hand[player][m] == gold){
                coinCountBefore++;
            }
        }
        //printf("Coin Count before: %d\n", coinCount);
        //printf("discard count before: %d\n", G.discardCount[player]);
        //printf("deckSize: %d, deck: %d, and hand: %d\n", deckSize, G.deckCount[0], G.handCount[0]); 
        //adventurerEffect(player, &G);   
        playAdventurer(player, &G);

        coinCount = 0;
        
        for(m = 0; m < G.handCount[player]; m++){
            if(G.hand[player][m] == copper || G.hand[player][m] == silver || G.hand[player][m] == gold){
                coinCount++;
            }
        }
        //printf("Coin Count after: %d\n", coinCount);
        //printf("discard count after: %d\n", G.discardCount[player]);
        discardCopper = 0;
        discardSilver = 0;
        discardGold = 0;
        for(x = 0; x < G.discardCount[player]; x++){
            if(G.discard[player][x] == copper) {
                discardCopper++;
            } else if(G.discard[player][x] == silver) {
                discardSilver++;
            } else if(G.discard[player][x] == gold) {
                discardGold++;
            }
        }
        int passed = 1;
        if(coinCount > (coinCountBefore + 2)){
            printf("Too many cards drawn: Test Failed\n\n");
            drawTestFailed++;
            passed = 0;
        }
        
        if( coinCount < coinCountBefore){
            printf("Fewer cards exist in hand than were first present: Test Failed\n\n");
            drawTestFailed++;
            passed = 0;
        }
        if(discardCopper != 0){
            printf("Copper was discarded: Test Failed\n\n");
            discardTestFailed++;
            passed = 0;
        }

        if(discardSilver != 0){
            printf("Silver was discarded: Test Failed\n\n");
            discardTestFailed++;
            passed = 0;
        }

        if(discardGold != 0){
            printf("Gold was discarded: Test Failed\n\n");
            discardTestFailed++;
            passed = 0;
        }

        if(passed == 1){
            printf("All Tests: Passed\n\n");
            testPassed++;
        }
   }
   
   printf("\n\n");
   printf("# of Tests Passed: %d\n", testPassed);
   printf("# of Draw Test Failures: %d\n", drawTestFailed++);
   printf("# of Discarded Test Failures: %d\n\n", discardTestFailed);
   
   return 0;
}