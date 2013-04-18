#ifndef exh
#define exh
#include "player.h"

class exPlayer:public player{
public:
  exPlayer(square **initTable);     // initialize player
  boardSquare nextMove();        // computes a next move for the player and stores coordinates in (xx,yy)
  void otherMove(boardSquare bs);// records the move of the opponent

private:
	int **table; // maintain my own copy of the board
	int xstreak[1][1]; //Keeps up a list of streak location. If there is a no current streak,
	//values = -1,-1. Otherwise contains the xy start location.
	int streak_length; //Currect steak length. At streak = 2, jump one to fool the opponent
	//from a block.
	string direction; //Contains possible directions. Choices are as follows:	
	//N, NE, E, SE, S, SW, W, NW
};
#endif
