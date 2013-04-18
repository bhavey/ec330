#include <iostream>
#include <cstdlib>
#include <string.h>
#include "player.h"
#include "exPlayer.h"
#define size 10
#define boardSize 10

int edge=size-3;

exPlayer::exPlayer(square **initTable) {
    xstreak=-1;
    ystreak=-1;
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

bool CheckDir(char s[2], int x, int y) {
    if (s=="N")
        if (y>3)
            return 1;
    else if (s=="NE")
        if ((y>3) && (x<edge))
            return 1;
    else if (s=="E")
        if (x<edge)
            return 1;
    else if (s=="SE")
        if ((y<edge) && (x<edge))
            return 1;
    else if (s=="S")
        if (y<edge)
            return 1;
    else if (s=="SW")
        if ((y<edge) && (x>3))
            return 1;
    else if (s=="W")
        if (x>3)
            return 1;
    else if (s=="NW")
        if ((y>3) && (x>3))
            return 1;
    return 0; //Nope!
}

boardSquare exPlayer::nextMove() {
    int x; //The two variables that we'll check for a location against.
    int y;
    int max_adj; //The amount of adjacent pieces
    boardSquare bs;
    while (table[bs.xx][bs.yy]!=blank) {
        x = rand()%boardSize;
        y = rand()%boardSize;
        bs.xx = x;
        bs.yy = y;
    }

    table[bs.xx][bs.yy]=ex;
    return bs;
}
