#include <iostream>
#include <cstdlib>
#include <string.h>
#include "player.h"
#include "exPlayer.h"
#define size 10
#define boardSize 10

static char directs[8][3] = { {'N'}, {'N', 'E'}, {'E'}, {'S', 'E'}, {'S'}, {'S', 'W'},
    {'W'}, {'N', 'W'} };

exPlayer::exPlayer(square **initTable) {
    xstreak=-1;
    ystreak=-1;
    streak_length=0;
    myColor=ex;
    direction[0]='d';
    strcpy(direction,"NO");
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

int* newCord(char s[2], int x, int y, int ret) {
    int *ptr;
    int returnVal[2];
    ptr=returnVal;
    if (ret==1) {
        returnVal[0]=x;
        returnVal[1]=y;
        return ptr;
    } else if (ret==2) { //+1 space.
        return ptr;
    }
    return ptr;
}

boardSquare exPlayer::nextMove() {
    int checkStreak=0;
    //char direct[2]="NW";
    boardSquare bs;
    int x,y;
    bool flagvar=1;
    char newdirect[2];
    int timing_var=0; //This var will keep going up as we look for a new spot.
    //if it exceeds 20, assume we'll go over the time limit, and jump out.

    //Simple idea is find a possible streak, go there.
    while (flagvar) {
        timing_var++;
        if (timing_var%20==0) { //jump out! Abort! Abort! Run out of time!
            while (table[bs.xx][bs.yy]!=blank) {
                bs.xx = rand()%boardSize;
                bs.yy = rand()%boardSize;
            }
            flagvar=0;
            break;
        }
        if (streak_length==0) { //Pick a random location. No streak as of right now.
            while (table[bs.xx][bs.yy]!=blank) {
                bs.xx = rand()%boardSize;
                bs.yy = rand()%boardSize;
            }
            for (int i=0; i<8; i++) { 
                checkStreak = this->CheckDir(directs[i],bs.xx,bs.yy,0);
                printf("checkStreak returned: %d\n",checkStreak);
                if (checkStreak) { //Found something. Throw it into direction.
                    strcpy(direction, directs[i]);
                    xstreak=bs.xx;
                    ystreak=bs.yy;
                    streak_length=1;
                    flagvar=0;
                }
            }
        } else { //We're on a streak. Go!
            x=xstreak+streak_length;
            y=ystreak+streak_length;
            checkStreak = this->CheckDir(direction,x,y,streak_length); 
            if (checkStreak) { //keep going on your streak!
                streak_length++;
                flagvar=0;
            } else { //Try another random location, try to find a new streak.
                streak_length=0;
                xstreak=-1;
                ystreak=-1;
                strcpy(direction,"NO");
            }
        }
    }

    table[bs.xx][bs.yy]=ex;
    return bs;
}

//Check if it's a valid direction to take!
 int exPlayer::CheckDir(char s[2], int x, int y, int length) {
    int edge=boardSize-4+streak_length;
    int bedge=3-streak_length;
    printf("x: %d, y: %d, s: %s\n",x,y,s);

    if (!strcmp(s,"N")) {
        if (y>bedge)
            return 1;
    } else if (!strcmp(s,"NE")) {
        if ((y>bedge) && (x<edge))
            return 1;
    } else if (!strcmp(s,"E")) {
        if (x<edge)
            return 1;
    } else if (!strcmp(s,"SE")) {
        if ((y<edge) && (x<edge))
            return 1;
    } else if (!strcmp(s,"S")) {
        if (y<edge)
            return 1;
    } else if (!strcmp(s,"SW")) {
        if ((y<edge) && (x>bedge))
            return 1;
    } else if (!strcmp(s,"W")) {
        if (x>bedge)
            return 1;
    } else if (!strcmp(s,"NW")) {
        if ((y>bedge) && (x>bedge))
            return 1;
    }
    return 0; //Nope!
}
