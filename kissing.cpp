#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <map>

using namespace std;

int main() { //Test program
    //Screw it. I don't even care. Just throw the whole damned dictionary into here.
    vector<string> pal; //Contains only the relevant palindromes
    vector<string> flip; //Contains flipable words.
    map<char,vector<string> > smap; //map of the starting chars.
    map<char,vector<string> > emap; //map of the ending chars.
    map<string, map<char,int> > tmap; //map containing a value for every individual pal.
    map<char,int> amap; //map containing the value of the kissing pal.

    fstream pald ("pal");
    fstream flp ("flip");

    char c='a'; //Start examining at a, loop through to z
    string entry;
    while (pald >> entry) { //Put the palindrome entries into a vector
        pal.push_back(entry);
    }

    while (flp >> entry) //Put the flip entries into a vector
        flip.push_back(entry);

    string tmp1;
    string tmp2;
    string tmp3;

//    map<string, map<char,int> > tmap; //map containing a value for every individual pal.
//    map<char,int> amap; //map containing the value of the kissing pal.

    int cur_pos=0;
    char first_char, cur_char, last_char;
    for (int i=0; i<pal.size(); i++) {
        first_char=*pal.at(i).begin();
        last_char=*(pal.at(i).end()-1);
        smap[first_char].push_back(pal.at(i));
        emap[last_char].push_back(pal.at(i));
        for (int j=0; j<pal.size(); j++) { //put all the palindromes in tmap
            cur_char=*(pal.at(i).begin()+j);
            tmap[pal.at(i)][cur_char]=1; //
        }
    }

//    for (int i=0; i<pal.size(); i++) {
}
