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
    vector<char> ar1;
    vector<char*> ar2;
    vector<char*> ar3;
    vector<char*> ar4;
    vector<char*> ar5;

    fstream in ("dictionary");
    string entry;

    while (in >> entry) { //Find relevant entries and put them in the vetors
        if (entry.length() == 1)
            ar1.push_back(*entry.c_str());
        if (entry.length() == 2) {
            ar2.push_back((char *)entry.c_str());
            printf("Found one at %s\n", (char *)entry.c_str());
        }
        if (entry.length() == 3)
            ar3.push_back((char *)entry.c_str());
        if (entry.length() == 4)
            ar4.push_back((char *)entry.c_str());
        if (entry.length() == 5)
            ar5.push_back((char *)entry.c_str());
    }

    printf("ar1: ");
    for (int i=0; i<ar1.size(); i++)
        printf("%c ",ar1.at(i));
    printf("\n\nar2: ");
    for (int i=0; i<ar2.size(); i++)
        printf("%s ",ar2.at(i));
    printf("\n\nar3: ");
/*    for (int i=0; i<ar3.size(); i++)
        printf("%s ",ar3.at(i));
    printf("\n\nar4: ");
    for (int i=0; i<ar4.size(); i++)
        printf("%s ",ar4.at(i));
    printf("\n\nar5: ");
    for (int i=0; i<ar5.size(); i++)
        printf("%s ",ar5.at(i));
*/
    return 0;
}
