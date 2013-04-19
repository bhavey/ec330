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

//Calculate the new coordinates
int* newCord(char s[2], int x, int y, int ret);

//Figure out the new streak coordinates.
int* streakCord(char s[2], int x, int y, int length);


boardSquare exPlayer::nextMove() {
    int checkStreak=0;
    //char direct[2]="NW";
    boardSquare bs;
    bool checkError=0;
    int x,y;
    int *ptr;
    int *ptr2;
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
            ptr2=streakCord(direction,xstreak,ystreak,streak_length);
//            x=xstreak+streak_length;
//            y=ystreak+streak_length;
            x=ptr2[0];
            y=ptr2[1];
            printf("on streak, x: %d, y: %d, length: %d\n",x,y,streak_length);
            checkStreak = this->CheckDir(direction,x,y,streak_length);
            printf("On streak, CheckDir returned %d\n",checkStreak);
            if (checkStreak) { //keep going on your streak!
                //printf("(1) streak newx: %d, newy: %d\n",newxy[0],newxy[1]);
                ptr=newCord(direction,x,y,checkStreak);
                //printf("(2) streak newx: %d, newy: %d\n",newxy[0],newxy[1]);
                streak_length+=checkStreak;
                bs.xx=ptr[0];
                bs.yy=ptr[1];
                checkError=this->ErrorCheck(bs.xx,bs.yy);
                if (checkError) { //well SOMETHING went wrong;
                    streak_length=0;
                    xstreak=-1;
                    ystreak=-2;
                    strcpy(direction,"NO");
                    flagvar=1;
                } else {
                    flagvar=0;
                    break;
                }
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
    int edge=boardSize-5+streak_length;
    int bedge=4-streak_length;
    int sameColor=0; //checks to see how many same color pieces you have in a row (if any)
    printf("x: %d, y: %d, s: %s\n",x,y,s);
    if (!strcmp(s,"N")) {
        if (y>bedge) {
            for (int i=0; i<4-streak_length; i++) { //Check for an enemy piece in your path.
                if (table[x][y-i]==oh) { //enemy in path.
                    return 0;
                }
                else if (table[x][y-i]==blank) {
                    if (sameColor==0)
                        sameColor=-1; //There was a blank before any same color pieces.
                    continue;
                }
                else if (table[x][y-i]==ex) {
                    if (sameColor!=-1)
                        sameColor++;
                    continue;
                } else {//unusable space.
                    return 0; 
                }
            }
            if (sameColor==-1) { //blank is next adjacent piece in streak
                return 1;
            } else { //There is a same color piece in your way. Skip over it!
                return (sameColor+1);
            }
        }
    } else if (!strcmp(s,"NE")) {
        if ((y>bedge) && (x<edge)) {
            for (int i=0; i<4-streak_length; i++) { //Check for an enemy piece in your path.
                if (table[x+i][y-i]==oh) { //enemy in path.
                    return 0;
                }
                else if (table[x+i][y-i]==blank) {
                    if (sameColor==0)
                        sameColor=-1; //There was a blank before any same color pieces.
                    continue;
                }
                else if (table[x+i][y-i]==ex) {
                    if (sameColor!=-1)
                        sameColor++;
                    continue;
                } else {//unusable space.
                    return 0; 
                }
            }
            if (sameColor==-1) { //blank is next adjacent piece in streak
                return 1;
            } else { //There is a same color piece in your way. Skip over it!
                return (sameColor+1);
            }
        }
    } else if (!strcmp(s,"E")) {
        if (x<edge) {
            for (int i=0; i<4-streak_length; i++) { //Check for an enemy piece in your path.
                if (table[x+i][y]==oh) { //enemy in path.
                    return 0;
                }
                else if (table[x+i][y]==blank) {
                    if (sameColor==0)
                        sameColor=-1; //There was a blank before any same color pieces.
                    continue;
                }
                else if (table[x+i][y]==ex) {
                    if (sameColor!=-1)
                        sameColor++;
                    continue;
                } else {//unusable space.
                    return 0; 
                }
            }
            if (sameColor==-1) { //blank is next adjacent piece in streak
                return 1;
            } else { //There is a same color piece in your way. Skip over it!
                return (sameColor+1);
            }
        }
    } else if (!strcmp(s,"SE")) {
        if ((y<edge) && (x<edge)) {
            for (int i=0; i<4-streak_length; i++) { //Check for an enemy piece in your path.
                if (table[x+i][y+i]==oh) { //enemy in path.
                    return 0;
                }
                else if (table[x+i][y+i]==blank) {
                    if (sameColor==0)
                        sameColor=-1; //There was a blank before any same color pieces.
                    continue;
                }
                else if (table[x+i][y+i]==ex) {
                    if (sameColor!=-1)
                        sameColor++;
                    continue;
                } else {//unusable space.
                    return 0; 
                }
            }
            if (sameColor==-1) { //blank is next adjacent piece in streak
                return 1;
            } else { //There is a same color piece in your way. Skip over it!
                return (sameColor+1);
            }
        }
    } else if (!strcmp(s,"S")) {
        if (y<edge) {
            for (int i=0; i<4-streak_length; i++) { //Check for an enemy piece in your path.
                if (table[x][y+i]==oh) { //enemy in path.
                    return 0;
                }
                else if (table[x][y+i]==blank) {
                    if (sameColor==0)
                        sameColor=-1; //There was a blank before any same color pieces.
                    continue;
                }
                else if (table[x][y+i]==ex) {
                    if (sameColor!=-1)
                        sameColor++;
                    continue;
                } else {//unusable space.
                    return 0; 
                }
            }
            if (sameColor==-1) { //blank is next adjacent piece in streak
                return 1;
            } else { //There is a same color piece in your way. Skip over it!
                return (sameColor+1);
            }
        }
    } else if (!strcmp(s,"SW")) {
        if ((y<edge) && (x>bedge)) {
            for (int i=0; i<4-streak_length; i++) { //Check for an enemy piece in your path.
                if (table[x-i][y+i]==oh) { //enemy in path.
                    return 0;
                }
                else if (table[x-i][y+i]==blank) {
                    if (sameColor==0)
                        sameColor=-1; //There was a blank before any same color pieces.
                    continue;
                }
                else if (table[x-i][y+i]==ex) {
                    if (sameColor!=-1)
                        sameColor++;
                    continue;
                } else {//unusable space.
                    return 0; 
                }
            }
            if (sameColor==-1) { //blank is next adjacent piece in streak
                return 1;
            } else { //There is a same color piece in your way. Skip over it!
                return (sameColor+1);
            }
        }
    } else if (!strcmp(s,"W")) {
        if (x>bedge) {
            for (int i=0; i<4-streak_length; i++) { //Check for an enemy piece in your path.
                if (table[x-i][y]==oh) { //enemy in path.
                    return 0;
                }
                else if (table[x-i][y]==blank) {
                    if (sameColor==0)
                        sameColor=-1; //There was a blank before any same color pieces.
                    continue;
                }
                else if (table[x-i][y]==ex) {
                    if (sameColor!=-1)
                        sameColor++;
                    continue;
                } else {//unusable space.
                    return 0; 
                }
            }
            if (sameColor==-1) { //blank is next adjacent piece in streak
                return 1;
            } else { //There is a same color piece in your way. Skip over it!
                return (sameColor+1);
            }
        }
    } else if (!strcmp(s,"NW")) {
        if ((y>bedge) && (x>bedge)) {
            for (int i=0; i<4-streak_length; i++) { //Check for an enemy piece in your path.
                if (table[x-i][y-i]==oh) { //enemy in path.
                    return 0;
                }
                else if (table[x-i][y-i]==blank) {
                    if (sameColor==0)
                        sameColor=-1; //There was a blank before any same color pieces.
                    continue;
                }
                else if (table[x-i][y-i]==ex) {
                    if (sameColor!=-1)
                        sameColor++;
                    continue;
                } else {//unusable space.
                    return 0; 
                }
            }
            if (sameColor==-1) { //blank is next adjacent piece in streak
                return 1;
            } else { //There is a same color piece in your way. Skip over it!
                return (sameColor+1);
            }
        }
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

int* streakCord(char s[2], int x, int y, int length) {
    printf("In streakCord. s: %s, x: %d, y: %d, length: %d\n",s,x,y,length);
    int xx, yy;
    int *ptr;
    int returnVal[2];
    ptr=returnVal;
    if (!strcmp(s,"N")) {
        xx=x;
        yy=y-length;
    } else if (!strcmp(s,"NE")) {
        xx=x+length;
        yy=y-length;
    } else if (!strcmp(s,"E")) {
        xx=x+length;
        yy=y;
    } else if (!strcmp(s,"SE")) {
        xx=x+length;
        yy=y+length;
    } else if (!strcmp(s,"S")) {
        xx=x;
        yy=y+length;
    } else if (!strcmp(s,"SW")) {
        xx=x-length;
        yy=y+length;
    } else if (!strcmp(s,"W")) {
        xx=x-length;
        yy=y;
    } else if (!strcmp(s,"NW")) {
        xx=x-length;
        yy=y-length;
    }
    printf("Done with ifs. xx: %d, yy: %d\n",xx,yy);
    returnVal[0]=xx;
    returnVal[1]=yy;
    printf("rV0: %d, rV1: %d\n",returnVal[0],returnVal[1]);
    ptr=returnVal;
    printf("ptr0: %d, ptr1: %d\n",ptr[0],ptr[1]);
    printf("Done in streakCord. s: %s, x: %d, y: %d, length: %d\n",s,x,y,length);
    return ptr;
}

bool exPlayer::ErrorCheck(int x, int y) {//Error check coordinates before moving there!
    if (table[x][y]!=blank) { //Will be an invalid move!
        return 1;
    }
    return 0;
}