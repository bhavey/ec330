#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;
//Stupid simple implementation.

int main() {
/* Solves the following crossword puzzle:
_#_#
#_#_
#_#_
__#_
#_#_
____
*/

    //These 5 vectors contain the contents of 1-5 letter words in the dictionary
    vector<string> ar1;
    vector<string> ar2;
    vector<string> ar3;
    vector<string> ar4;
    vector<string> ar5;

    fstream in ("dictionary");
    string entry;

    while (in >> entry) { //Find relevant entries and put them in the vetors
        if (entry.length() == 1)
            ar1.push_back(entry);
        if (entry.length() == 2)
            ar2.push_back(entry);
        if (entry.length() == 3)
            ar3.push_back(entry);
        if (entry.length() == 4)
            ar4.push_back(entry);
        if (entry.length() == 5)
            ar5.push_back(entry);
    }


    string row1;
    string col1, col2, col3;
    col3=ar1.at(1); //This is seperate from everything else
    row2=ar1.at(5); //can set them to anything
    for (int i=0; i<ar3.size(); i++) { //row1 is the smallest, set to the outermost.
        row1=ar2.at(i);
        for (int j=0; j<ar5.size(); j++) {
            col1=ar5.at(j);
            if (col1[2]==row3[1]) { //col1 and row3 match!
                for (int k=0; k<ar4.size(); k++) {
                    row4=ar4.at(k);
                    if (row4[1]==col1[4]) { //col1 and row4 match!
                        for (int l=0; l<ar5.size(); l++) {
                            col2=ar5.at(l);
                            if (col2[4]==row4[3]) {
                                i=ar2.size();
                                j=ar5.size();
                                k=ar4.size();
                                l=ar5.size();
                                printf("Here!\n");
                            }
                        }
                    }
                }
            }
        }
    }

    printf("r1: %s, r2: %s, r3: %s, r4: %s, c1: %s, c2: %s\n",row1.c_str(),row2.c_str(),row3.c_str(),
        row4.c_str(),col1.c_str(),col2.c_str());

    return 0;
}
