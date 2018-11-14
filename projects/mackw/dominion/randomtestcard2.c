// randomtestcard2.c
// By: William Taylor Mack
// CS362 Assignment-4

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "assert.h"
#include "dominion.h"
#include "rngs.h"

#define NUM_TESTS 10000
#define MAX_HAND_COUNT 15
#define MAX_DISCARD_COUNT 50
#define MAX_DECK_COUNT 50

int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

int main(int argc, char** argv) {
    
    struct gameState* state = newGame();
    int card, ret_val, currentPlayer, verbose;
    int initialNumActions, initialHandCount, initialNumBuys, initialCoins, test;
    int initialDiscardCount, initialDeckCount, empty, copperCount;
    int initialPlayedCardCount, money, player, curCard;
    enum CARD cutpurseCard;
    enum CARD copperCard;
    
    verbose = 1; /* Set verbose to 1 to see final and initial values */
    empty = -523; /* This number indicates that a spot in an array does not have a card */
    currentPlayer = 0;  
    cutpurseCard = cutpurse;
    copperCard = copper;
    srand(time(NULL));
    
    for (test = 0; test < NUM_TESTS; test++) {  
        
        /* "money" is a Boolean that indicates 
        whether or not players' hands are filled with copper */ 
        money = rand() % 2;
        
        initialDeckCount = 10 + rand() % (MAX_DECK_COUNT - 9);
        initialHandCount = 1 + rand() % MAX_HAND_COUNT;
        initialDiscardCount = rand() % MAX_DISCARD_COUNT;
        initialNumActions = rand() % 10;
        initialNumBuys = rand() % 5;
        initialPlayedCardCount = rand() % 5;
        initialCoins = rand() % 8;
        
        state->numPlayers = MAX_PLAYERS - (rand() % 2);
        state->deckCount[currentPlayer] = initialDeckCount;
        for (player = 0; player < state->numPlayers; player++)
            state->handCount[player] = initialHandCount;
        state->discardCount[currentPlayer] = initialDiscardCount;
        state->numActions = initialNumActions;
        state->numBuys = initialNumBuys;
        state->playedCardCount = initialPlayedCardCount;
        state->coins = initialCoins;
        
        
        /* Put some cards in hand */
        for (player = 0; player < state->numPlayers; player++) {
            for (card = 0; card < MAX_HAND; card++) {
                state->hand[player][card] = empty;
            }
            
            for (card = 0; card < state->handCount[player]; card++) {
                state->hand[player][card] = money * copperCard;
                if (verbose) printf("%d ", state->hand[player][card]);
            }
            if (verbose) printf("    ");
        }
        if (verbose) printf("\n");
        
        /* initialize deck and discard pile to empty */
        for (card = 0; card < MAX_DECK; card++) {
            state->discard[currentPlayer][card] = empty;
            state->deck[currentPlayer][card] = empty;
        }
        
        /* Put some cards in discard pile */
        for (card = 0; card < state->discardCount[currentPlayer]; card++) {
            state->discard[currentPlayer][card] = 0;
        }
        
        /* Put some cards in deck */
        for (card = 0; card < state->deckCount[currentPlayer]; card++) {
            state->deck[currentPlayer][card] = 0;
        }
        
        
        if (verbose)
            printf("calling cardEffect()...\n");
        ret_val = cardEffect(cutpurseCard, 0, 0, 0, state, 2, NULL);
        
        if (verbose) {
            for (player = 0; player < state->numPlayers; player++) {
                for (card = 0; card < state->handCount[player]; card++) {
                    printf("%d ", state->hand[player][card]);
                }
                printf("    ");
            }
            printf("\n");
        }
        
        if (verbose) {
            printf("initialNumBuys: %d\n", initialNumBuys);
            printf("state->numBuys: %d\n", state->numBuys);
            printf("initialCoins: %d\n", initialCoins);
            printf("state->coins: %d\n", state->coins);
            printf("initialNumActions: %d\n", initialNumActions);
            printf("state->numActions: %d\n", state->numActions);
            printf("initialHandCount: %d\n", initialHandCount);
            printf("state->handCount[currentPlayer]: %d\n", state->handCount[currentPlayer]);
            printf("initialDiscardCount: %d\n", initialDiscardCount);
            printf("state->discardCount[currentPlayer]: %d\n", state->discardCount[currentPlayer]);
            printf("initialPlayedCardCount: %d\n", initialPlayedCardCount);
            printf("state->playedCardCount: %d\n\n", state->playedCardCount);
        }
        
        assert(0 == ret_val);
        assert(initialNumActions == state->numActions);
        assert(initialNumBuys == state->numBuys);
        
        /* I don't even know what purpose state->coins serves in dominion.c */
        //assert(initialCoins - state->numPlayers == state->coins);
        
        /* Make sure opponents' purses have been cut!  */
        for (player = 0; player < state->numPlayers; player++) {
            
            copperCount = 0;                    
            for (curCard = 0; curCard < state->handCount[player]; curCard++) {
                if (state->hand[player][curCard] == copperCard)
                    copperCount++;
            }
                                    
            if (!money) {               
                assert(initialPlayedCardCount + 1 == state->playedCardCount);
                assert(copperCount == 0);
            }
            
            else {              
                assert(initialPlayedCardCount + state->numPlayers == state->playedCardCount);
                
                if (player != currentPlayer)
                    assert(copperCount == initialHandCount - 1);
                    
                else
                    assert(copperCount == state->handCount[player]);
            }               
        }

        
        /* Make sure discard pile hasn't somehow been messed up*/
        for (card = 0; card < state->discardCount[currentPlayer]; card++) {
            assert(state->discard[currentPlayer][card] != empty);
        }
        
        /* Make sure deck hasn't somehow been messed up*/
        for (card = 0; card < state->deckCount[currentPlayer]; card++) {
            assert(state->deck[currentPlayer][card] == 0);
        }           
    }
    
    printf("Cutpurse card passed all tests\n");
    
    return 1;
}
