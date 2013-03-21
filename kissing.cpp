#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <map>

using namespace std;
bool fullalph(map<char,int>);
void printpal(vector<string>);
int test_in(string s, vector<string> pal);
void add_map(map<char,int> &out, map<string,map<char,int> > &temp, string s);

int main() { //Test program
    //Screw it. I don't even care. Just throw the whole damned dictionary into here.
    vector<string> pal; //Contains only the relevant palindromes
    vector<string> flip; //Contains flipable words.
    vector<string> kiss; //The kissing palindrome!
    map<char,vector<string> > smap; //map of the starting chars.
    map<char,vector<string> > emap; //map of the ending chars.
    map<string, map<char,int> > tmap; //map containing a value for every individual pal.
    map<char,int> amap; //map containing the value of the kissing pal.

    fstream pald ("pal");
    fstream flp ("flip");

    char c='a'; //Start examining at a, loop through to z
    string entry;
    while (pald >> entry) //Put the palindrome entries into a vector
        if (entry.length()!=1)
            pal.push_back(entry);

    for (int i=0; i<pal.size(); i++)
        printf("%s\n",pal.at(i).c_str());


    while (flp >> entry) //Put the flip entries into a vector
        if (entry.length()!=1)
            flip.push_back(entry);

    string tmp1;
    string tmp2;
    string tmp3;

    int cur_pos=0;
    char first_char, cur_char, last_char;
    for (int i=0; i<pal.size(); i++) {
        first_char=*pal.at(i).begin();
        last_char=*(pal.at(i).end()-1);
        smap[first_char].push_back(pal.at(i));
        emap[last_char].push_back(pal.at(i));
        for (int j=0; j<pal.size(); j++) { //put all the palindromes in tmap
            cur_char=*(pal.at(i).begin()+j);
            tmap[pal.at(i)][cur_char]=1; //map all the possible chars
        }
    }

    char cur_lo;
    char start='a';
    int newflag;
    int jflag, kflag, lflag, mflag, nflag;
//    map<char,vector<string> > smap; //map of the starting chars.
//    map<char,vector<string> > emap; //map of the ending chars.
//    map<string, map<char,int> > tmap; //map containing a value for every individual pal.
//    map<char,int> amap; //map containing the value of the kissing pal.
//map<char,int> add_map(map<string,map<char,int> > &temp_map, string s)

    map<char,int> temp_map;
    add_map(amap, tmap, "reiter");
    char a='a';

//    for (int i=0; i<26; i++)
  //      printf("%c: %d\n",a+i,amap[a+i]);

    return 0;
}

void add_map(map<char,int> &out, map<string,map<char,int> > &temp, string s) {
    char c='a';
    printf("string letter matches: \n");
    for (int i=0; i<26; i++)
        printf("%c: %d\n",c+i,temp[s][c+i]);

    for (int i=0; i<26; i++)
        out[c+i]+=temp[s][c+1];
}

bool fullalph(map<char,int> inmap) {
    char start='a';
    for (int i=0; i<26; i++) {
        if (inmap[start+i]==0)
            return false;
    }
    return true;
}

void printpal(vector<string> pal) {
    for (int i=0; i<pal.size(); i++)
        printf("%s, ",pal.at(i).c_str());
    printf("\n");
}

int test_in(string s, vector<string> pal) {
    for (int i=0; i<pal.size(); i++) { //make sure there are no repeats
        if (s==pal.at(i))           //in the palindrome.
            return 1;
    }
    return 0;
}
