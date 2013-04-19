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

int* newCord(char s[2], int x, int y, int ret);

boardSquare exPlayer::nextMove() {
    int checkStreak=0;
    //char direct[2]="NW";
    boardSquare bs;
    int x,y;
    int *ptr;
    //int newxy[2];
    //ptr=newxy;
    bool flagvar=1;
    char newdirect[2];
    int timing_var=0; //This var will keep going up as we look for a new spot.
    //if it exceeds 20, assume we'll go over the time limit, and jump out.

    printf("direction: %s\n",direction);
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
                    //ptr=newxy;
                    ptr=newCord(direction,bs.xx,bs.yy,checkStreak);
                    streak_length+=checkStreak;
                    xstreak=bs.xx;
                    ystreak=bs.yy;
                    bs.xx=ptr[0];
                    bs.yy=ptr[1];
                    flagvar=0;
                    break;
                }
            }
        } else { //We're on a streak. Go!
            x=xstreak+streak_length;
            y=ystreak+streak_length;
            printf("on streak, x: %d, y: %d\n",x,y);
            checkStreak = this->CheckDir(direction,x,y,streak_length);
            printf("On streak, CheckDir returned %d\n",checkStreak);
            if (checkStreak) { //keep going on your streak!
                //printf("(1) streak newx: %d, newy: %d\n",newxy[0],newxy[1]);
                ptr=newCord(direction,x,y,checkStreak);
                //printf("(2) streak newx: %d, newy: %d\n",newxy[0],newxy[1]);
                streak_length+=checkStreak;
                bs.xx=ptr[0];
                bs.yy=ptr[1];
                flagvar=0;
                break;
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


int* newCord(char s[2], int x, int y, int ret) {
    printf("In newCord: %s; x: %d, y: %d, ret: %d\n",s,x,y,ret);
    int *ptr;
    int xx, yy;
    int returnVal[2];
    ptr=returnVal;
    if (ret==1) { //on current space.
        xx=x;
        yy=y;
    } else if (ret==2) { //+1 space.
        if (!strcmp(s,"N")) {
            xx=x;
            yy=y-1;
        } else if (!strcmp(s,"NE")) {
            xx=x+1;
            yy=y-1;
        } else if (!strcmp(s,"E")) {
            xx=x+1;
            yy=y;
        } else if (!strcmp(s,"SE")) {
            xx=x+1;
            yy=y+1;
        } else if (!strcmp(s,"S")) {
            xx=x;
            yy=y+1;
        } else if (!strcmp(s,"SW")) {
            xx=x-1;
            yy=y+1;
        } else if (!strcmp(s,"W")) {
            xx=x-1;
            yy=y;
        } else if (!strcmp(s,"NW")) {
            xx=x-1;
            yy=y-1;
        }
    } else if (ret==3) { //+2 spaces
        if (!strcmp(s,"N")) {
            xx=x;
            yy=y-2;
        } else if (!strcmp(s,"NE")) {
            xx=x+2;
            yy=y-2;
        } else if (!strcmp(s,"E")) {
            xx=x+2;
            yy=y;
        } else if (!strcmp(s,"SE")) {
            xx=x+2;
            yy=y+2;
        } else if (!strcmp(s,"S")) {
            xx=x;
            yy=y+2;
        } else if (!strcmp(s,"SW")) {
            xx=x-2;
            yy=y+2;
        } else if (!strcmp(s,"W")) {
            xx=x-2;
            yy=y;
        } else if (!strcmp(s,"NW")) {
            xx=x-2;
            yy=y-2;
        }
    } else if (ret==4) { //+3 spaces over!
        if (!strcmp(s,"N")) {
            xx=x;
            yy=y-3;
        } else if (!strcmp(s,"NE")) {
            xx=x+3;
            yy=y-3;
        } else if (!strcmp(s,"E")) {
            xx=x+3;
            yy=y;
        } else if (!strcmp(s,"SE")) {
            xx=x+3;
            yy=y+3;
        } else if (!strcmp(s,"S")) {
            xx=x;
            yy=y+3;
        } else if (!strcmp(s,"SW")) {
            xx=x-3;
            yy=y+3;
        } else if (!strcmp(s,"W")) {
            xx=x-3;
            yy=y;
        } else if (!strcmp(s,"NW")) {
            xx=x-3;
            yy=y-3;
        }
    }
    returnVal[0]=xx;
    returnVal[1]=yy;
    printf("Done in newCord, rV[0]: %d, rV[1]: %d, xx: %d, yy: %d\n",returnVal[0],
        returnVal[1],xx,yy);
    ptr=returnVal;
    printf("ptr[0]: %d, ptr[1]: %d\n",ptr[0],ptr[1]);
    return ptr;
}