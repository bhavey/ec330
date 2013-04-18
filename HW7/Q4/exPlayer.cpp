#include <iostream>
#include <cstdlib>
#include "player.h"
#include "exPlayer.h"
#define size 10
#define boardSize 10

exPlayer::exPlayer(square **initTable) {
  myColor=ex;
    table = new int*[size];
    for (int ii=0; ii<size; ii++) {
        table[ii]=new int[size];
    }
    for (int ii=0; ii<size; ii++) {
        for (int jj=0; jj<size; jj++) {
			table[ii][jj]=initTable[ii][jj];
        }
    }
}

void exPlayer::otherMove(boardSquare bs) {
	table[bs.xx][bs.yy]=(myColor==ex?oh:ex);
}

boardSquare exPlayer::nextMove() {
    int x; //The two variables that we'll check for a location against.
    int y;
    int max_adj; //The amount of adjacent pieces
    boardSquare bs;
    while (table[bs.xx][bs.yy]!=blank) {
        bs.xx = rand()%boardSize;
        bs.yy = rand()%boardSize;
    }
    table[bs.xx][bs.yy]=ex;
    return bs;
}
