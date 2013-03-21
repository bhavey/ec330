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
void zero_map(map<char,int> &out);
void add_map(map<char,int> &out, map<string,map<char,int> > &temp, string s);
void printmap(map<char,int> &in,bool nl);
void printvec(map<char,vector<string> > &in);

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
        for (int j=0; j<pal.at(i).length(); j++) { //put all the palindromes in tmap
            cur_char=*(pal.at(i).begin()+j);
            tmap[pal.at(i)][cur_char]+=1; //map all the possible chars
        }
    }

    printvec(smap);
//    printvec(emap);

    char cur_lo;
    char start='a';
    int newflag;
    int jflag, kflag, lflag, mflag, nflag;
//    map<char,vector<string> > smap; //map of the starting chars.
//    map<char,vector<string> > emap; //map of the ending chars.
//    map<string, map<char,int> > tmap; //map containing a value for every individual pal.
//    map<char,int> amap; //map containing the value of the kissing pal.
//map<char,int> add_map(map<string,map<char,int> > &temp_map, string s)

    zero_map(amap);
//    add_map(amap, tmap, "poop");
    char a='a';

//    printmap(amap,0);

    return 0;
}

void zero_map(map<char,int> &out) { //zeros all the letters in out.
    for (int i=0; i<26; i++)
        out['a'+i]=0;
}

void add_map(map<char,int> &out, map<string,map<char,int> > &temp, string s) {
    for (int i=0; i<26; i++) //Adds together out+temp[s], stores in out.
        out['a'+i]+=static_cast<int>(temp[s]['a'+i]);
}

bool fullalph(map<char,int> inmap) { //check if every letter is present in the map
    for (int i=0; i<26; i++)
        if (inmap['a'+i]==0)
            return false;
    return true;
}

void printpal(vector<string> pal) { //Prints the vector of strings
    for (int i=0; i<pal.size(); i++)
        printf("%s, ",pal.at(i).c_str());
    printf("\n");
}

void printvec(map<char,vector<string> > &in) { //Prints the map of the vector of strings
    for (int i=0; i<26; i++) {
        printf("\n%c: ",'a'+i);
        for (int j=0; j<in['a'+i].size(); j++)
            printf("%s%s",in['a'+i].at(j).c_str(),(j==in['a'+i].size()-1)?"\n":", ");
    }
    printf("\n");
}

void printmap(map<char,int> &in,bool nl) { //prints map, if nl=1, print newlines
    for (int i=0; i<26; i++)
        printf("%c: %d%s",'a'+i,in['a'+i],nl?"\n":(i==25?"\n":", "));
}

int test_in(string s, vector<string> pal) {
    for (int i=0; i<pal.size(); i++) { //make sure there are no repeats
        if (s==pal.at(i))           //in the palindrome.
            return 1;
    }
    return 0;
}
