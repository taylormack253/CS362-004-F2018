// randomtestcard2.c
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
#include <math.h>

#define CARD_TEST "Council Room"
#define ITERATIONS 10000

/* Global variables. */
int fail_count_cardEffect = 0;              // Counts failure instances for cardEffect().
int fail_count_discardCard = 0;             // Counts failure instances for discardCard().
int fail_count_drawCard = 0;                // Counts failure instances for drawCard().
int fail_count_numBuys = 0;                 // Counts failure instances for numBuys().
int fail_count_deckHandCount_Active = 0;    // Counts failure instances for deckHandCount() for active player.
int fail_count_deckHandCount_Opponent = 0;  // Counts failure instances for otherPlayerDeckHand() for opponent players.

/* Function declarations. */
void testCouncil_Room(int p, struct gameState *post);

int main ()
{
    printf("Performing random tests of %s card\n", CARD_TEST);

    int i, n;           // Loop counters.
    int player;         // Tracks current player number.
    int deckCount;      // Counts number of cards in deck.
    int handCount;      // Counts number of cards in hand.
    int discardCount;   // Counts number of cards in discard pile.
    int totalPlayers[] = {2, 3, 4};  // Possible numbers of players to test.
    struct gameState G; // Initializes gameState.

    srand(time(NULL));  // Provides random seed from system time.

    /* Initializes gameState to a random value. Referenced from testDrawCard.c. */
    for (n = 0; n < ITERATIONS; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char*)&G)[i] = floor(Random() * 256); // Provides random values for initial gameState.
        }
        /* Chooses random values for numPlayers, numBuys, playedCardCount, and deck, hand, and discard pile counts. */
        G.numPlayers = totalPlayers[rand() % 3];
        G.numBuys = 1;
        G.playedCardCount = floor(Random() * (MAX_DECK - 1));
        player = G.numPlayers - 2;
        deckCount = floor(Random() * MAX_DECK);
        handCount = floor(Random() * MAX_HAND);
        discardCount = floor(Random() * MAX_DECK);
        G.whoseTurn = player;

        /* Initializes hand, deck, and discard pile of opponent players. */
        for (i = 0; i < G.numPlayers; i++)
        {
            G.deckCount[i] = deckCount;
            G.handCount[i] = handCount;
            G.discardCount[i] = discardCount;
        }

        /* Calls the test function for the FUT. */
        testCouncil_Room(player, &G);
    }

    /* Counts total number of failures for all tests. */
    int totalFailCount = fail_count_cardEffect + fail_count_discardCard + fail_count_drawCard
                    + fail_count_deckHandCount_Active + fail_count_numBuys;

    printf("\nTest Summary:\n");

    if (totalFailCount == 0)
    {
        printf ("\nAll random tests passed!\n\n");
        printf("Results:\n");
        printf("Testing of drawCard() passed on %d total iterations.\n", ITERATIONS);
        printf("Testing of cardEffect() passed on %d total iterations.\n", ITERATIONS);
        printf("Testing of discardCard() passed on %d total iterations.\n", ITERATIONS);
        printf("A correct number of buys was returned in %d instances.\n", ITERATIONS);
        printf("Each opponent's hand, deck, and discard pile returned correctly in %d instances.\n", ITERATIONS);
        printf("The active player's hand, deck, and discard pile returned correctly in %d instances.\n", ITERATIONS);
        printf("\n");
    }
    else
    {
        printf ("\nTESTING FAILED!\n\n");
        printf("Results:\n");
        if (fail_count_drawCard > 0)
            printf("Testing of drawCard() failed on %d total iterations.\n", fail_count_drawCard);
        else
            printf("Testing of drawCard() passed on %d total iterations.\n", ITERATIONS);
        if (fail_count_cardEffect > 0)
            printf("Testing of cardEffect() failed on %d total iterations.\n", fail_count_cardEffect);
        else
            printf("Testing of cardEffect() passed on %d total iterations.\n", ITERATIONS);
        if (fail_count_discardCard > 0)
            printf("Testing of discardCard() failed on %d total iterations.\n", fail_count_discardCard);
        else
            printf("Testing of discardCard() passed on %d total iterations.\n", ITERATIONS);
        if (fail_count_numBuys > 0)
            printf("An incorrect number of buys was returned in %d instances.\n", fail_count_numBuys);
        else
            printf("A correct number of buys was returned in %d instances.\n", ITERATIONS);
        if (fail_count_deckHandCount_Opponent > 0)
            printf("An opponent's hand, deck, or discard pile returned incorrectly in %d instances.\n", fail_count_deckHandCount_Opponent);
        else
            printf("Each opponent's hand, deck, and discard pile returned correctly in %d instances.\n", ITERATIONS);
        if (fail_count_deckHandCount_Active > 0)
            printf("The active player's hand, deck, or discard pile returned incorrectly\nin %d instances.\n", fail_count_deckHandCount_Active);
        else
            printf("The active player's hand, deck, and discard pile returned correctly\nin %d instances.\n", ITERATIONS);
        printf("\n");
    }
    return 0;
}


/*******************************************************************************
 * Name: void testCouncil_Room(int p, struct gameState *post)
 * Description: Tests the Council Room card.
 * Arguments: An int representing the player number, and a struct gameState
 *            containing the state of the current game.
 *
 * References the checkDrawCard() function from testDrawCard.c
 *******************************************************************************/
void testCouncil_Room(int p, struct gameState *post)
{
    struct gameState pre;   // Allows for manipulation of the gameState during test.
    int bonus = 0;          // Counts value of bonus.
    int r;                  // Stores result of cardEffect().
    int s;                  // Stores result of first drawCard() for active player.
    int t;                  // Stores result of second drawCard() for active player.
    int u;                  // Stores result of third drawCard() for active player.
    int v;                  // Stores result of fourth drawCard() for active player.
    int w;                  // Stores result of drawCard() for opponent.
    int x;                  // Stores result of discardCard().
    int i;                  // Loop counter.

    /* Sets up initial gameState prior to manipulation during test. */
    memcpy(&pre,post,sizeof(struct gameState));

    /* Invokes and stores the council_room case from cardEffect. */
    r = cardEffect(council_room, 0, 0, 0, post, 0, &bonus);

    /* Draws 4 cards, per the Council Room specification. */
    s = drawCard(p, &pre);
    t = drawCard(p, &pre);
    u = drawCard(p, &pre);
    v = drawCard(p, &pre);

    /* Increments number of buys (+1), per the Council Room specification. */
    pre.numBuys++;

    /* Draws +1 card for each opponent, per the Council Room specification. */
    for (i = 0; i < pre.numPlayers; i++)
    {
        if (i != p) // Draws only for the opponent players.
        {
            w = drawCard(i, &pre);

            /* Tests for failure of drawcard. */
            if (w == -1 && pre.deckCount[i] != 0)
            {
                fail_count_drawCard++;
            }
        }
    }

    /* Places used Council Room card in the discard pile. */
    x = discardCard(0, p, &pre, 0);

    /* Counts expected hand and deck. */
    int postHandCount = post->handCount[p];
    int postDeckCount = post->deckCount[p];

    /* Counts actual hand and deck. */ 
    int preHandCount = pre.handCount[p];
    int preDeckCount = pre.deckCount[p];

    /* Tests if resulting numBuys matches expected numBuys. */
    if (pre.numBuys != post->numBuys)
    {
        fail_count_numBuys++;
    }

    /* Tests for failure of first drawcard. */
    if (s == -1 && pre.deckCount[p] != 0)
    {
        fail_count_drawCard++;
    }
    /* Tests for failure of second drawcard. */
    if (t == -1 && pre.deckCount[p] != 0)
    {
        fail_count_drawCard++;
    }
    /* Tests for failure of third drawcard. */
    if (u == -1 && pre.deckCount[p] != 0)
    {
        fail_count_drawCard++;
    }
    /* Tests for failure of fourth drawcard. */
    if (v == -1 && pre.deckCount[p] != 0)
    {
        fail_count_drawCard++;
    }

    /* Tests cardEffect() and discardCard() for failure. */
    if (!(r == 0 && x == 0))
    {
        if (r)  // Tests result of cardEffect().
        {
            fail_count_cardEffect++;
        }
        if (x)  // Tests result of discardCard().
        {
            fail_count_discardCard++;
        }
    }

    /* Tests if expected values match actual values for hand and deck of active player. */
    if (!(postHandCount == preHandCount && postDeckCount == preDeckCount))
    {
        fail_count_deckHandCount_Active++;
    }

    /* Tests if expected values match actual values for hand and deck of each opponent. */
    for (i = 0; i < pre.numPlayers; i++)
    {
        if (i != p)
        {
            if (!(post->handCount[i] == pre.handCount[i] &&
                  post->deckCount[i] == pre.deckCount[i]))
            {
                      fail_count_deckHandCount_Opponent++;
            }
        }
    }
}