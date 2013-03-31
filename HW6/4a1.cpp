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
____
_###
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

    char first_char;
    char last_char;
    string row1, row2;
    string col1;
    for (int i=0; i<ar4.size(); i++) {
        row1=ar4.at(i);
        first_char=row1[0];
        for (int j=0; j<ar3.size(); j++) {
            col1=ar3.at(j);
            last_char=col1[2];
            if (first_char==col1[0]) {
                for (int k=0; k<ar4.size(); k++) {
                    row2=ar4.at(k);
                    if (row2[0]==last_char) {
                        i=ar4.size();
                        j=ar3.size();
                        k=ar4.size();
                    }
                }
            }
        }
    }

    printf("%s, %s, %s\n",row1.c_str(),col1.c_str(),row2.c_str());
    printf("%s\n%c###\n%s\n",row1.c_str(),col1[1],row2.c_str());
    return 0;
}
