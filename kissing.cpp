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

//    map<string, map<char,int> > tmap; //map containing a value for every individual pal.
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

//    map<char,vector<string> > smap; //map of the starting chars.
//    vector<string> kiss; //The kissing palindrome!
//tmap is the individ ones
    char cur_lo;
    char start='a';
    int newflag;
    int jflag, kflag, lflag, mflag, nflag;
    for (int i=0; i<pal.size(); i++) { //form the actual kissing palindromes!
        start='a';
        for (int j=0; j<26; j++)
            amap[start+j]=0; //clear out the amap!
        for (int j=0; j<26; j++) {
            newflag=0;
            lflag=0;
            kiss.clear(); //clean it every time we reach here!
//            for (int k=0; k<26; k++) {
                for (int l=0; l<(emap[start+j].size())&&!lflag; l++) {
                    if (!newflag)
                        kiss.push_back(emap[start+j].at(l)); //Put this piece on the top.
                    else {
                        tmp1=emap[start+j].at(l);
                        test_in(tmp1, kiss);
                    }
                    for (int m=0; m<26; m++) //Add to the main maping
                        amap[start+m]=amap[start+m]+tmap[emap[start+j].at(l)][start+m];
                    for (int m=0; m<smap[emap[start+j].size()].size(); m++) {
                        nflag=0;
                        tmp1=smap[start+j].at(m);
                        for (int n=0; n<kiss.size(); n++) { //make sure there are no repeats
                            if (tmp1==kiss.at(n)) {         //in the palindrome.
                                nflag=1;
                                break;
                            }
                        }

                        kiss.push_back(tmp1);
                        for (int n=0; n<26; n++)
                            amap[start+n]=amap[start+n]+tmap[emap[start+j].at(l)][start+n];
                        if (fullalph(amap)) {
                            printpal(kiss);
                            lflag=1;
                        }
//                            printf("Found a palindrome!\n");
                    }
                }
  //          }
        }
        printf("i:%d\n",i);
    }
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
