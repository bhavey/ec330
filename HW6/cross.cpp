#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <map>

#define MAX_LINES 500
//Set value to 1, 2, or 3, depending on if solving for part i, ii, or iii
#define PART 1

using namespace std;

struct Word {
    int x,y; //Coordinates on the crossword puzzle.
    int length;
    char *word;
    int *intersects; //For every n bits in the word, there can be an intersecting row for
    //columns or column for rows. This array contains what that particular word is.
    //Value is -1 if there is no intersect.
};

class Cross {
public:
    Cross() {rows=1; cols=1;} //Need to start on row/column index 1 instead of 0 for seg faulting.
    ~Cross() {};
    void addLine(string); //Adds a line to the crossword puzzle.
    void removeLine(); //Remove previous line.
    void definePuzzle(); //After adding all the lines as desired, define the rows/columns.
    void setRow(int,string); //Set the "int" row to string
    void clearRow(int); //Clear a given row.
    void setCol(int,string); //Set the "int" column to string
    void clearColumn(int); //Clear a given column.
    void printCrossword(); //Prints the crossword puzzle.
    void printRowData(int); //Prints a row's data.
    void printColData(int); //Prints a column's data.

private:
    int rows; //# of rows
    int cols; //# of columns
    bool defined; //If defined=1, we can setrows/columns, else we can't. Gets defined after calling definePuzzle()
    char crossword[MAX_LINES][MAX_LINES]; //The actual crossword contents
    Word Rows[MAX_LINES/2]; //The fillable rows. There are "n" of them, they have "n" starts
    Word Cols[MAX_LINES/2]; //Fillable columns.
    int row_starts[MAX_LINES][MAX_LINES]; //Starting coordinates of rows.
    int col_starts[MAX_LINES][MAX_LINES]; //Starting coordinates of cols.
    int tot_rows, tot_cols;
};

void Cross::definePuzzle() { //Define the rows.
    if (PART==1) { //Part 4ai
        Rows[0].x=0;
        Rows[0].y=0;
        Rows[0].length=4;
        Rows[0].word=(char *)"____";
        Rows[0].intersects[0]=0;
        for (int i=1; i<4; i++)
            Rows[0].intersects[i]=-1;

        Rows[1].x=0;
        Rows[1].y=2;
        Rows[1].length=4;
        Rows[1].word=(char *)"____";
        Rows[1].intersects[0]=0;
        for (int i=1; i<4; i++)
            Rows[0].intersects[i]=-1;

        Cols[0].x=0;
        Cols[0].y=0;
        Cols[0].length=3;
        Cols[0].word=(char *)"___";
        Cols[0].intersects[0]=0;
        Cols[0].intersects[1]=-1;
        Cols[0].intersects[2]=1;
    }
    if (PART==2) { //Part 4aii
        Rows[0].x=0;
        Rows[0].y=0;
        Rows[0].length=1;
        Rows[0].word=(char *)"_";
        Rows[0].intersects[0]=-1;

        Rows[1].x=2;
        Rows[1].y=0;
        Rows[1].length=1;
        Rows[1].word=(char *)"_";
        Rows[1].intersects[0]=-1;

        Rows[2].x=0;
        Rows[2].y=3;
        Rows[2].length=2;
        Rows[2].word=(char *)"__";
        Rows[2].intersects[0]=-1;
        Rows[2].intersects[1]=0;

        Cols[0].x=1;
        Cols[0].y=1;
        Cols[0].length=4;
        Cols[0].word=(char *)"____";
        for (int i=0; i<4; i++) {
            if (i==2) {
                Cols[0].intersects[2]=2;
            } else {
                Cols[0].intersects[i]=-1;
            }
        }

        Cols[1].x=3;
        Cols[1].y=1;
        Cols[1].length=4;
        Cols[1].word=(char *)"____";
        for (int i=0; i<4; i++) {
            Cols[1].intersects[i]=-1;
        }
    }
    if (PART==3) { //Part 4aiii
        Rows[0].x=0;
        Rows[0].y=4;
        Rows[0].length=3;
        Rows[0].word=(char *)"___";
        Rows[0].intersects[0]=0;
        Rows[0].intersects[1]=-1;
        Rows[0].intersects[2]=1;

        Cols[0].x=0;
        Cols[0].y=0;
        Cols[0].length=5;
        Cols[0].word=(char *)"_____";
        for (int i=0; i<5; i++) {
            if (i==4) {
                Cols[0].intersects[i]=0;
            } else {
                Cols[0].intersects[i]=-1;
            }
        }

        Cols[1].x=2;
        Cols[1].y=0;
        Cols[1].length=5;
        Cols[1].word=(char *)"_____";
        for (int i=0; i<5; i++) {
            if (i==4) {
                Cols[1].intersects[i]=0;
            } else {
                Cols[1].intersects[i]=-1;
            }
        }

        Cols[2].x=4;
        Cols[2].y=0;
        Cols[2].length=5;
        Cols[2].word=(char *)"_____";
        for (int i=0; i<5; i++) {
            Cols[2].intersects[i]=-1;
        }
    }
    return;
}


void Cross::addLine(string s) {
    if (rows==1) { //Can define the row length.
        cols=s.length()-1;
        for (int i=0; i<s.length(); i++)
            crossword[0][i] = '-'; //Set the border!
    } else if ((s.length()-1)!=cols) { //Check for wrong row length.
        printf("Improper row length. Rows must all be the same length as the first length, %d long.\n",cols+1);
        return;
    }
    for (int i=0; i<s.length(); i++) {
        crossword[rows][i] = *(s.begin()+i);
    }
    rows++;
    return;
}

void Cross::removeLine() {
    if (rows>1) {
        rows--;
        if (rows==1) {
            cols=0;
        }
    } else {
        printf("There are no rows to delete.\n");
    }
    return;
}


void Cross::printCrossword() { //Prints the crossword puzzle.
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            printf("%c",crossword[i][j]);
        }
        printf("\n");
    }
    return;
}
int main() { //Test program
    Cross cross;

    fstream in ("Crossword.txt");
    string entry;

    while (in >> entry) { //Fill the crossword puzzle in!
        cross.addLine(entry);
    }
    cross.printCrossword();
    cross.definePuzzle();
    cross.printCrossword();

    return 0;
}
