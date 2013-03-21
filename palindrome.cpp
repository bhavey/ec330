//Trie data structure. File contains Trie/Node classes
//Concept taken from http://login2win.blogspot.com/2011/06/c-tries.html
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <map>
//Total of 234946 words in dictionary

using namespace std;

string flipstring(string s) { //return a mirrored string
    string s2;
    s2=s;
    reverse(s2.begin(),s2.end()); //from std::algorithm, reverses the order of elements
    return s2;
}

bool stringmirror(string s) { //return true if the string is a palidrome itself
    string s2;
    s2=s;
    reverse(s2.begin(),s2.end()); //flip
    if (s==s2)
        return true;
    else
        return false;
}

int main() { //Test program
    //Screw it. I don't even care. Just throw the whole damned dictionary into here.
    vector<string> Dictionary;
    vector<string> pal; //Contains only the relevant palindromes
    vector<string> flip; //Contains flipable words.
    map<char,int> amap; //map of the dictionary.

    fstream dict ("Dictionary");

    char c='a'; //Start examining at a, loop through to z
    string entry;
    while (dict >> entry) { //Put the dictionary entries into a vector
        //Convert entry to lower case. Upper cases won't count as multiple entries this way.
        transform(entry.begin(), entry.end(), entry.begin(), ::tolower);
        Dictionary.push_back(entry);
    }

    string tmp1;
    string tmp2;
    string tmp3;
    //There are repeats in the dictionary due to Lower/Upper cases, delete repeats.
    for (int i=0; i<Dictionary.size()-1; i++) { //cull out repeats
        tmp1=Dictionary.at(i);
        tmp2=Dictionary.at(i+1);
        if (tmp1==tmp2)
            Dictionary.erase(Dictionary.begin()+i);
    }

    int cur_pos=0;
    for (int i=0; i<Dictionary.size(); i++) {
        tmp3=Dictionary.at(i);
        if (tmp3[0]==c) { //Map the positions where these will be in the dictionary vector.
            amap[c]=cur_pos;
            c++;
        }
        cur_pos++;
    }

    char last_char;
    bool breakvar=0;
    //Now that we have repeats culled out, find the flipable and palindrotic words.
    for (int i=0; i<Dictionary.size(); i++) {
        breakvar=0;
        if (i%10000==0) {
            printf("At iteration %d\n",i);
            printf("%s, %s, %c\n",tmp1.c_str(),tmp2.c_str(),*tmp2.begin());
        }
        tmp1=Dictionary.at(i);
        tmp2=flipstring(tmp1);
        for (int j=0; j<pal.size(); j++) {
            if (tmp2==pal.at(j)) { //we've already seen this!
                breakvar=1;
                break;
            }
        }
        if (breakvar)
            continue;
        last_char = *tmp2.begin();
        for (int j=amap[last_char]; j<amap[last_char<'z'?last_char+1:Dictionary.size()]; j++) {
            tmp3=Dictionary.at(j);
            if (tmp2==tmp3) {
                printf("%s is a palindrome of %s\n",tmp1.c_str(),tmp2.c_str());
                pal.push_back(tmp1);
                break;
            }
        }
        if (stringmirror(tmp1))
            flip.push_back(tmp1);
    }

    for (int i=0; i<flip.size(); i++) //cull out repeats
        printf("%s ",flip.at(i).c_str());
    printf("\n");
}
