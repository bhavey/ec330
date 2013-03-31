#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;

int main() {
/* Solves the following crossword puzzle:
____
_###
____
*/
    int size[6]; //contains the # of letters for every n letter word

    char *ar1; //one letter length.
    char *ar2[2]; //two letter length.
    char *ar3[3]; //three letter length.
    char *ar4[4]; //four letter length.
    char *ar5[5]; //five letter length.

    fstream in ("dictionary");
    string entry;

    while (in >> entry) { //Fill the crossword puzzle in!
        if (entry.length() == 1)
            size[1]++;
        if (entry.length() == 2)
            size[2]++;
        if (entry.length() == 3)
            size[3]++;
        if (entry.length() == 4)
            size[4]++;
        if (entry.length() == 5)
            size[5]++;
    }
    printf("1: %d, 2: %d, 3: %d, 4: %d, 5: %d\n",size[1],size[2],size[3],size[4],size[5]);

    char ar1
    return 0;
}
