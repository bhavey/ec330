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

int main() {
    int flagvar=0;
    long int matches=0;
    regex_t re;
    regmatch_t match;
    FILE *writeover;
    writeover = fopen("NewData.txt","w");
    fclose(writeover);
    char * pch;
    const char *p1;
    const char *p2;
    long int numb;
    string word;
    string dict_word;
    fstream dict ("odict");
    fstream in ("BigData.txt");
    fstream out ("NewData.txt");
    while (in >> word) {
        //make word lower cased.
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        //cut out the empty strings!
        pch=strtok((char*)word.c_str(),"0123456789");
        while (pch != NULL) {
            dict.seekg(0); //Bring the dictionary to the beginning!
            numb++;
            if (numb%1000==0)
                printf("At word: %ld\n",numb);
//            out << pch;
//            out << "\n";
            while (dict >> dict_word) {
                p1=word.c_str();
                p2=dict_word.c_str();
                if (strlen(p2) > strlen(p1) ) {
                    break;
                }
                regcomp(&re, p2, 0);
//                while (regexec(&re, p1, 1, &match, 0) == 0) {
              //  printf("p1: %s, p2: %s\n",p1,p2);
               // if (strcmp(p1,"oo")==0) {
                  //  printf("here!\n");
               // }
                while (regexec(&re, p1, 1, &match, 0) == 0) {
                //    printf("p1: %s, p2: %s\n",p1,p2);
                    matches++;
                    printf("%s contains %s\n",p1,p2);
                    p1 += match.rm_eo;
                    flagvar=1;
                    usleep(200000);
                }
                if (flagvar) {
                    flagvar=0;
                    break;
                }
                usleep(1);
                regfree(&re);
            }
            pch = strtok(NULL, "0123456789");
        }
    }
    in.close();
    return 0;
}
