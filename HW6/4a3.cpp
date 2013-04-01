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

    char first, last;
    string row1;
    string col1, col2, col3;
    col3=ar5.at(1); //This is seperate from everything else
    for (int i=0; i<ar3.size(); i++) { //row1 is the smallest, set to the outermost.
        row1=ar3.at(i);
        first=row1[0];
        last=row1[2];
        for (int j=0; j<ar5.size(); j++) {
            col1=ar5.at(j);
            if (col1[4]==first) //col1 and row1 match!
                break;
        }
        for (int j=0; j<ar5.size(); j++) {
            col2=ar5.at(j);
            if (col2[4]==last) //col2 and row1 match!
                break;
        }
    }

    printf("c1: %s, r1: %s, c2: %s, c3: %s\n",col1.c_str(),row1.c_str(),col2.c_str(),col3.c_str());
    return 0;
}
