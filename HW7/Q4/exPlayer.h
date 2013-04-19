
#ifndef exh
#define exh
#include "player.h"
#include <string.h>

class exPlayer:public player{
public:
  exPlayer(square **initTable);     // initialize player
  boardSquare nextMove();        // computes a next move for the player and stores coordinates in (xx,yy)
  void otherMove(boardSquare bs);// records the move of the opponent
  int CheckDir(char s[3], int x, int y, int length); //Checks the directionality on the board,
  //see if can move 4 (or less) pieces in any given direction. A return of 0 means no (blocked,
  //or not enough board space), a return of 1 means a move at location, 2 means 2 ahead,
  //3 means 3 ahead, 4 means 4 ahead, and victory!

private:
	int **table; // maintain my own copy of the board
	int xstreak; //Keeps up a list of streak location. If there is a no current streak,
	int ystreak;
	//values = -1,-1. Otherwise contains the xy start location.
	int streak_length; //Currect steak length. At streak = 2, jump one to fool the opponent
	//from a block.
	char direction[3]; //Contains possible directions. Choices are as follows:	
	//N, NE, E, SE, S, SW, W, NW,
	//NO means not on a streak.
};
#endif
