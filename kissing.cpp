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
bool maps_diff(map<string,map<char,int> > &map1, map<char,int> &map2, map<char,int> &map3, string s);//True is map1/2 have overlaping char

int main() { //Test program
    //Screw it. I don't even care. Just throw the whole damned dictionary into here.
    vector<string> pal; //Contains only the relevant palindromes
    vector<string> kiss; //The kissing palindrome!
    vector<string> final_kiss; //The kissing palindrome!
    map<char,vector<string> > start_map; //map of the starting chars.
    map<string, map<char,int> > alph_map; //map containing a value for every individual pal.
    map<char,int> all_maps; //map containing the value of the kissing pal.
    map<char,int> end_map; //map of the ending chars already present in palindrome.
    int i, j, k;

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
    bool break_val=0;
    int length, final_length=99999;
    char last_char;
    string tmp;
    string tmp2;
    int itr;
    bool jumpflag;
    int kiss_size;

    for (i=0; i<pal.size(); i++) { //Loop through, starting with every possible palindrome first
        break_val=0;
        jumpflag=1;
        itr=0;
        zero_map(all_maps); //Clear out the mapping deal
        zero_map(end_map);
        kiss.clear(); //Clear out the kissing palindrome.
        tmp=pal.at(i);
        kiss.push_back(tmp); //Put the ith palendrome at the root.
        last_char=*(tmp.end()-1); //find the last char in the kissing palindrome
        end_map[last_char]=1; //Add this to the end_map
        add_maps(all_maps,alph_map,tmp);
        printf("here!\n");
        for (k=0; k<start_map[*(kiss.at(itr).end()-1)].size(); k++) { //put
            jumpflag=0;
            kiss_size=kiss.size();
            printf("before:\n");
            printpal(kiss);
            int workaround; //Check if the first char at kiss.itr is the last possible one in pal
            string itr_word;
            string this_shit;
            printf("itr word: %s\n",kiss.at(itr).c_str());
            printf("this shit: %s\n",start_map[*(kiss.at(itr).begin())].back().c_str());
            itr_word=kiss.at(itr).c_str();
            this_shit=start_map[*(kiss.at(itr).begin())].back().c_str();
            if (strcmp(itr_word.c_str(),this_shit.c_str())==0) {
                printf("Yeah, last one in the line!\n");
            } else {
                itr==0?itr=0:itr--;
            }
            kiss.erase(kiss.begin()+itr+1, kiss.end());
            zero_map(all_maps); //Clear out the mapping deal
            zero_map(end_map);
            printf("after:\n");
            printpal(kiss);
            printf("i: %d, j: %d, k: %d, itr: %d, last: %c\n",i,j,k,itr,last_char);
            for (int l=0; l<kiss.size(); l++) {
                add_maps(all_maps,alph_map,kiss.at(l));
                end_map[*(kiss.at(l).end()-1)]=1; //Add this to the end_map
            }
            usleep(1000);
            last_char=*(kiss.at(itr).end()-1);
            //pop the deal back x amount.
            for (j=k; j<start_map[last_char].size(); j++) {
                jflag=0;
                tmp2=start_map[last_char].at(j);
                if (test_vector(kiss,tmp2)) {//Word is already in the palindrome.
                    printf("Skipping %s because %s is already in the palindrome:\n",tmp2.c_str(),tmp2.c_str());
                    jflag=1;
                    if (j==(start_map[last_char].size()-1))
                        jumpflag=1; //We got locked out.
                }
                if (maps_diff(alph_map,all_maps,end_map,tmp2)) { //No new letters in palindrome
                //Just realized this jumps way too loosely!
                //It jumps whenever they have the same character map.
                //Should only skip if they have the same character map *and* the last letter has
                //yes to be touched.
                    printf("Skipping %s because map has nothing to add.",tmp2.c_str());
                    jflag=1;
                    if (j==(start_map[last_char].size()-1))
                        jumpflag=1; //We got locked out.
                }
                if (jflag==1) {//Something went wrong, so continue on.
                    if (jumpflag) {
                        itr++;
                        break; //get out!
                    } else
                        continue;
                }
                kiss.push_back(tmp2); //tmp2 fits the necessary criteria. Put it on the kissing pal
                last_char=*(tmp2.end()-1); //find the last char in the kissing palindrome
                add_maps(all_maps,alph_map,tmp2);
                printpal(kiss);
                printf("\n\n");
      //          usleep(200000);
                if(fullalph(all_maps)) {
                    printf("Complete palindrome:\n");
                    printpal(kiss);
                    printf("\n\n");
                    printf("Alphabet Map:\n");
                    printmap(all_maps,0);
                    usleep(20000);
                    sleep(5);
                } else {
                    j=-1;
                    continue;
                }
            }
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
        if (static_cast<int>(temp[s]['a'+i]))
            out['a'+i]=1;
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

bool maps_diff(map<string,map<char,int> > &map1, map<char,int> &map2, map<char,int> &map3, string s) {
    if (map3[*(s.end()-1)]==0)
        return false;
    for (int i=0; i<26; i++) {
        if (skipqxz('a'+i))
            continue;
        if (map1[s]['a'+i]!=map2['a'+i])
            return false;
    }
    return true;
}
