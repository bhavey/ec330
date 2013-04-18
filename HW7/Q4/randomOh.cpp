#include <iostream>
#include <cstdlib>
#include "player.h"
#include "randomOh.h"
#define size 10
#define boardSize 10

ohPlayer::ohPlayer(square **initTable) {
  myColor=oh;
  table = new int*[size];
  for (int ii=0; ii<size; ii++)
    table[ii]=new int[size];
  for (int ii=0; ii<size; ii++)
    for (int jj=0; jj<size; jj++)
      table[ii][jj]=initTable[ii][jj];
}

void ohPlayer::otherMove(boardSquare bs) {
  table[bs.xx][bs.yy]=(myColor==ex?oh:ex);
}

boardSquare ohPlayer::nextMove() {
  boardSquare bs;
  while (table[bs.xx][bs.yy]!=blank)
    {bs.xx = rand()%boardSize; bs.yy = rand()%boardSize; }
  table[bs.xx][bs.yy]=oh;
  return bs;
}
