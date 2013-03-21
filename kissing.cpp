#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <map>

using namespace std;
bool fullalph(map<char,int>); //Sees if the map contains all the alphabetic characters
void zero_map(map<char,int> &out); //Sets the alphabetic map to zero
//Adds the map into itself
void add_map(map<char,int> &out, map<string,map<char,int> > &temp, string s);
void printpal(vector<string>); //prints the kissing palindrome string
void printmap(map<char,int> &in,bool nl); //prints a map, nl =newline, otherwise just uses spaces
void printvec(map<char,vector<string> > &in); //prints the maps of characters to strings
bool test_vector(vector<string> pal, string s); //tests if a string is inside of a vector
bool skipqxz(char c); //skips the character if it's q, x, or z
bool maps_diff(map<char,int> &map1, map<char,int> &map2);//True is map1/2 have overlaping char

int main() { //Test program
    //Screw it. I don't even care. Just throw the whole damned dictionary into here.
    vector<string> pal; //Contains only the relevant palindromes
    vector<string> kiss; //The kissing palindrome!
    map<char,vector<string> > start_map; //map of the starting chars.
    map<string, map<char,int> > alph_map; //map containing a value for every individual pal.
    map<char,int> all_maps; //map containing the value of the kissing pal.

    fstream pald ("pal");

    string entry;
    while (pald >> entry) //Put the palindrome entries into a vector
        if (entry.length()!=1)
            pal.push_back(entry);

    for (int i=0; i<pal.size(); i++)
        printf("%s\n",pal.at(i).c_str());

    char first_char, cur_char, last_char;
    for (int i=0; i<pal.size(); i++) {
        first_char=*pal.at(i).begin();
        start_map[first_char].push_back(pal.at(i));
        for (int j=0; j<pal.at(i).length(); j++) { //put all the palindromes in the alpha map
            cur_char=*(pal.at(i).begin()+j); //find the char at location 
            alph_map[pal.at(i)][cur_char]+=1; //map all the possible chars
        }
    }

    printvec(start_map);
    char cur_lo;
//    map<char,vector<string> > smap; //map of the starting chars.
//    map<string, map<char,int> > tmap; //map containing a value for every individual pal.
//    map<char,int> amap; //map containing the value of the kissing pal.
//map<char,int> add_map(map<string,map<char,int> > &temp_map, string s)

    zero_map(all_maps);
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
    for (int i=0; i<26; i++) {
        if (skipqxz('a'+i))
            continue;
        if (inmap['a'+i]==0)
            return false;
    }
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
    for (int i=0; i<26; i++) {
        printf("%c: %d%s",'a'+i,in['a'+i],nl?"\n":(i==25?"\n":", "));

    }
}

bool test_vector(string s, vector<string> pal) {
    for (int i=0; i<pal.size(); i++) //make sure there are no repeats
        if (s==pal.at(i))           //in the palindrome.
            return 1;
    return 0;
}

bool skipqxz(char c) { //skips the character if it's q, x, or z
    if ( (c=='q')||(c=='x')||(c=='z') )
        return true;
    else
        return false;
}

bool maps_diff(map<char,int> &map1, map<char,int> &map2) {
    for (int i=0; i<26; i++) {
        if (skipqxz('a'+i))
            continue;
        if (map1['a'+i]!=map2['a'+i])
            return true;
    }
    return false;
}
