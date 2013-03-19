using namespace std;
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <limits>
#include <vector>
#include <string>
#include <regex.h>
//#include <algorithm>

int main() {
    ifstream readf ("dictionary");
    regex_t re;
    regmatch_t match;
    FILE *ndict;
    ndict = fopen("ndict","w");
    char cur_str[25];
    char prev_str[25];
    while (readf >> cur_str) {
        for (int i=0; i<(sizeof(cur_str)/sizeof(char)); i++)
            cur_str[i]=tolower(cur_str[i]);
        regcomp(&re, "n$", REG_EXTENDED);
        if (regexec(&re, cur_str, 1, &match, 0) == 0) {
            //Ends with an n. My name is Ben. This is no good.
            printf("%s ends a n.\n",cur_str);
        } else {
            //This time print the string
            if (strcmp(cur_str,prev_str)!=0)
                fprintf(ndict, "%s", cur_str);
        }
        //Check this versus the previous string.
        strcpy(prev_str,cur_str);
    }
    fclose(ndict);
    readf.close();
    printf("Done!\n");
    return 0;
}
