y#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <map>

#define MAX_LINES 500

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

void Cross::definePuzzle() { //Define the rows.
    //Defining the puzzle works as follows, it goes row by row, first finding rows.
    //It then runs through the row, finding and setting columns. When setting columns it
    //Makes sure that they are not stated above.
    Word tmprow;
    Word tmpcol;
    tot_rows=0;
    tot_cols=0;
    for (int i=1; i<rows; i++) { //Run through that biddie!
        for (int j=0; j<cols; j++) {
            if ((crossword[i][j]=='_') && (crossword[i][j+1]=='_')) { //New Row!
                tmprow.length=0; //Clean the tmprow.
                tmprow.x=j;
                tmprow.y=i;
                for (int k=0; k<cols; k++) {
                    tmprow.intersects[k]=-1;
                    tmprow.word[k]='';
                }
                row_starts[i][j]=tot_rows;
                for (int k=j; k<cols; k++) { //new row! Run through k, then set j to k at the end
                    tmprow.word[k-tmprow.x]='_';
                    if (crossword[i][k]=='_')
                        tmprow.length++;
                    if (crossword[i-1][k]=='_') { //Intersecting column, must have been declared
                    //alread, no need to make due to implementation. Find it's intersection location
                        for (int l=i-1; l>1; l--) {
                            if (crossword[l-1][k]!='_') { //Starting location of the column.
                                tmprow.intersects[k-tmprow.x]=col_starts[l][k];
                                //Add the column intersect.
                                Cols[col_starts[l][k]].intersects[i-l]=tot_rows;
                                break;
                            }
                        }
                    }
                    if ((crossword[i+1][k]=='_') && (crossword[i-1][k]!='_')) {
                    //Start of a column, set the intersect, then declare the new column.
                        col_starts[i][j]=tot_cols;
                        tmprow.intersects[k-tmprow.x]=tot_cols;
                        tmpcol.length=0;
                        tmpcol.x=i;
                        tmpcol.y=j;
                        for (int k=0; k<rows; k++) {
                            tmpcol.intersects[k]=-1;
                            tmpcol.word[k]='';
                        }
                        for (int l=i; l++; 1) { //Go until we reach the end!
                            if (crossword[i+l]!='_')
                                break; //we're done here...
                            length++;
                            tmpcol.word[l-i]='_';
                        }

                        Cols[tot_cols]=tmpcol;
                        Cols[tot_cols].intersects[i]=tot_rows;
                        tot_cols++;
                    }
                }
                Rows[tot_rows]=tmprow; //Set the Row value to the tmprow.
                tot_rows++;
            } else if ((crossword[i][j]=='_') && (crossword[i][j+1]!='_')) { //new column, or 1 letr
                if (crossword[i+1][j]!='_') { //single word

                } else { //new column
                    //Clean it up!
                    tmpcol.length=0;
                    tmpcol.x=i;
                    tmpcol.y=j;
                    for (int k=0; k<rows; k++) {
                        tmpcol.intersects[k]=-1;
                        tmpcol.word[k]='';
                    }
                    col_starts[i][j]=tot_cols;
                }
            }
            //Now set j=k, so we can go forward in the line.
            j=k;
        }
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

    return 0;
}
