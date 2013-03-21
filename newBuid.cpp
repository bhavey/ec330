//Trie data structure. File contains Trie/Node classes
//Concept taken from http://login2win.blogspot.com/2011/06/c-tries.html
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>

using namespace std;

int findID(string); //returns the amount of BU ID's present in the current file.

int main() { //Test program
    fstream in ("BigData.txt");

    long long int tot_hits=0;
    long long int hits=0;
    int check=0;

    string word;
    long int pos=0;

    while (in >> word) { //Read BigData in word for word.
        check=findID(word);
        tot_hits+=check;
        if (pos%10000000==0)
            printf("At word %ld, total matches: %lld\n",pos,tot_hits);
        if (check) { //Non-zero amount of BUIDs in the current string!
        }
        pos++;
    }
    printf("Finished at word %ld, total matches: %lld\n",pos,tot_hits);
    return 0;
}

int findID(string s) { //returns the amount of BU ID's present in the current file.
    int matches=0;
    for (int i=0; (i+8)<s.length(); i++) { //Make sure it's longer!
        if (s[i]=='U') { //check if it starts with U
            for (int j=1; j<10; j++) {
                if ((j<9)&&(isdigit(s[i+j])) ) { //Makes sure the 8 characters following U are #s
                    continue;
                } else if ( (j==9) && (!isdigit(s[i+j])) ) { //Make sure no digits after 8 digits
                    matches++;
                    i+=j; //Push the loop forward.
                } else {
                    i+=j; //There was a non digit within the 8, or a digit on the 9th, go forward
                    break;
                }
            }
        } else
            continue; //Didn't start with U, continue on through the string.
    }
    return matches; //Done!
}
