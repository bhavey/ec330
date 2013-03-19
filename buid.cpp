using namespace std;
#include <iostream>
#include <fstream>
#include <math.h>
#include <regex.h>
#include <stdio.h>
#include <limits>
#include <vector>

int main() {
    regex_t re;
    char file[] = "hello777world99yew U46525972 I8909do23!";
    const char *p = file;
    regmatch_t match;

    fstream in ("BigData.txt");
    vector<string> words;
    string word;

    if( !in )
        return 0;
    int numb=0;

    long long pos=0;
//    for 
    while (in >> word) {
        numb++;
        if (numb%10000==0)
            printf("numb: %d\n",numb);
        if (numb%100000==0) {
            pos = in.tellg();
            in.close();
            fstream in ("BigData.txt");
            in.seekg(pos);
            printf("pos: %lld\n",pos);
        }
        p=word.c_str();
        regcomp(&re, "U[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]", REG_EXTENDED);
        while(regexec(&re, p, 1, &match, 0) == 0) {
//            printf("%.*s\n", (int)(match.rm_eo - match.rm_so), &p[match.rm_so]);
            p += match.rm_eo;
        }
    }

    return 0;
}
