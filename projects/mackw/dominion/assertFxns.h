/////////////////////////////////////////////////////////
#ifndef DOMINION_ASSERT_H
#define DOMINION_ASSERT_H

void assertCustom(int boolean, char * message);

void assertGameState(int player, struct gameState * oldG, struct gameState * newG);

#endif //DOMINION_ASSERT_H