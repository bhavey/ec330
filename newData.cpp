using namespace std;
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <regex.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

int main() {
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
        //cut out the empty strings!
        pch=strtok((char*)word.c_str(),"0123456789");
        while (pch != NULL) {
            dict.seekg(0); //Bring the dictionary to the beginning!
            numb++;
            if (numb%10==0)
                printf("At word: %ld\n",numb);
//            out << pch;
//            out << "\n";
            while (dict >> dict_word) {
                p1=word.c_str();
                p2=dict_word.c_str();
                if (strlen(p2) > strlen(p1) ) {
                    break;
                }
                regcomp(&re, p2, REG_ICASE);
                while (regexec(&re, p1, 1, &match, 0) == 0) {
        //                    printf("%s contains %s\n",p1,p2);
                    p1 += match.rm_eo;
                }
                regfree(&re);
            }
            pch = strtok(NULL, "0123456789");
        }
    }
    in.close();
    return 0;
}
