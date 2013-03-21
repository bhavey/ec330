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
void add_maps(map<char,int> &out, map<string,map<char,int> > &temp, string s);
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
    vector<string> final_kiss; //The kissing palindrome!
    map<char,vector<string> > start_map; //map of the starting chars.
    map<string, map<char,int> > alph_map; //map containing a value for every individual pal.
    map<char,int> all_maps; //map containing the value of the kissing pal.
    int i, j;

    fstream pald ("pal");

    string entry;
    while (pald >> entry) //Put the palindrome entries into a vector
        if (entry.length()!=1)
            pal.push_back(entry);

    char first_char, cur_char;
    for (int i=0; i<pal.size(); i++) {
        first_char=*pal.at(i).begin();
        start_map[first_char].push_back(pal.at(i));
        for (int j=0; j<pal.at(i).length(); j++) { //put all the palindromes in the alpha map
            cur_char=*(pal.at(i).begin()+j); //find the char at location
            alph_map[pal.at(i)][cur_char]=1; //map all the possible chars
        }
    }
    zero_map(all_maps);

//bool test_vector(vector<string> pal, string s); //tests if a string is inside of a vector
//bool skipqxz(char c); //skips the character if it's q, x, or z
//bool maps_diff(map<char,int> &map1, map<char,int> &map2);//True is map1/2 have overlaping char
//map<char,vector<string> > start_map; //map of the starting chars.
//map<string, map<char,int> > alph_map; //map containing a value for every individual pal.
//map<char,int> all_maps; //map containing the value of the kissing pal.
    bool jflag;
    int length, final_length=99999;
    char last_char;
    string tmp;
    string tmp2;
    string test="poop";
    bool testb;
    testb=test_vector(pal,static_cast<string>(test));

    for (i=0; i<pal.size(); i++) { //Loop through, starting with every possible palindrome first
        zero_map(all_maps); //Clear out the mapping deal
        kiss.clear(); //Clear out the kissing palindrome.
        tmp=pal.at(i);
        kiss.push_back(tmp); //Put the ith palendrome at the root.
        last_char=*(tmp.end()-1); //find the last char in the kissing palindrome
        add_maps(all_maps,alph_map,tmp);
//        printpal(kiss);
//        printmap(all_maps,0);
        for (j=0; j<start_map[last_char].size(); j++) {
            jflag=0;
            printf("\n\n------------------------------------------------------------------\n\nCurrent Palindrome: ");
            printpal(kiss);
            tmp2=start_map[last_char].at(j);
                printf("all maps:\n");
                printmap(all_maps,0);
                printf("\n%s map:\n",tmp2.c_str());
                printmap(alph_map[tmp2],0);
                printf("\n\n\n");
            if (test_vector(kiss,tmp2)) {//Word is already in the palindrome.
                printf("Skipping %s because %s is already in the palindrome:\n",tmp2.c_str(),tmp2.c_str());
                jflag=1;
            }
//            if (maps_diff(all_maps,all_maps)) { //No new letters in palindrome
            if (maps_diff(alph_map[tmp2],all_maps)) { //No new letters in palindrome
                printf("Skipping %s because map has nothing to add.",tmp2.c_str());
                jflag=1;
                usleep(2000000);
            }
            if (jflag==1) //Something went wrong, so continue on.
                continue;
            kiss.push_back(tmp2); //tmp2 fits the necessary criteria. Put it on the kissing pal
            last_char=*(tmp2.end()-1); //find the last char in the kissing palindrome
            printpal(kiss);
            usleep(200000);
        }
    }
    return 0;
}

void zero_map(map<char,int> &out) { //zeros all the letters in out.
    for (int i=0; i<26; i++)
        out['a'+i]=0;
}

void add_maps(map<char,int> &out, map<string,map<char,int> > &temp, string s) {
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

bool skipqxz(char c) { //skips the character if it's q, x, or z
    if ( (c=='q')||(c=='x')||(c=='z') )
        return true;
    else
        return false;
}

bool test_vector(vector<string> pal, string s) {
    for (int i=0; i<pal.size(); i++) //make sure there are no repeats
        if (s==pal.at(i))           //in the palindrome.
            return true;
    return false;
}

bool maps_diff(map<char,int> &map1, map<char,int> &map2) {
    printf("Maps_Dif: \n");
    printmap(map1,0);
    printf("\n");
    printmap(map2,0);
    printf("\n");
    for (int i=0; i<26; i++) {
        if (skipqxz('a'+i))
            continue;
        if (map1['a'+i]!=map2['a'+i])
            return false;
    }
    return true;
}
