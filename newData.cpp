using namespace std;
#include <time.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <regex.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

/*char numtospace(char in) {
    if (isdigit(in))
        return ' ';
    else
        return in;
}*/

int main() {
    int flagvar=0;
    long int matches=0;
    int prev_dic_length;
    int cur_dic_length;
    regex_t re;
    regmatch_t match;
    FILE *writeover;
    writeover = fopen("NewData.txt","w");
    fclose(writeover);
    char * pch;
    const char *p1;
    const char *p2;
    char *realword;
    long int numb;
//    string realword;
    string word;
    string dict_word;
    fstream dict ("odict");
    fstream in ("BigData.txt");
    fstream out ("NewData.txt");
    //find the length of odict
    int i;
    dict.seekg(0,dict.end);
    int dict_length = dict.tellg();
    dict.seekg(0,dict.beg);
    while (in >> word) {
        //make word lower cased.
        transform(word.begin(), word.end(), word.begin(), ::tolower);
//        transform(word.begin(), word.end(), word.begin(), numtospace);
        //cut out the empty strings!
  //      pch=strtok((char*)word.c_str()," 0123456789");
      //  while (pch != NULL) {
            dict.seekg(0); //Bring the dictionary to the beginning!
            numb++;
            if ((numb%50==0))
                printf("Matches: %ld. At word: %ld,%s\n",matches,numb,word.c_str());
            while (dict >> dict_word) {
                if (dict.tellg()==dict_length) {
                    //we're at the end of the dictionary.. something has gone wrong.
                    dict.seekg(0,dict.beg);
                    break;
                }
                p1=pch;
                p2=dict_word.c_str();
                if (strlen(p2) > strlen(p1) ) {
                    break; //word is longer then the dictionary entries from here on out!
                }
                regcomp(&re, p2, REG_EXTENDED);
                while (regexec(&re, p1, 1, &match, 0) == 0) {
                    matches++;
                    p1 += match.rm_eo;
                    flagvar=1;
                    usleep(0);
                }
                if (flagvar) {
                    flagvar=0;
                        continue;
                }
                regfree(&re);
            }
        //    pch = strtok(NULL, "0123456789 ");
       // }
    }
    in.close();
    return 0;
}
