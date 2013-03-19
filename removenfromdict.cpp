using namespace std;
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <limits>
#include <vector>
#include <string>
#include <regex.h>

int main() {
    ifstream readf ("dictionary");
    regex_t re;
    regmatch_t match;
    FILE *ndict;
    ndict = fopen("ndict","w");
    char cur_str[25];
    while (readf >> cur_str) {
        regcomp(&re, "n$", REG_EXTENDED);
        if (regexec(&re, cur_str, 1, &match, 0) == 0) {
            //Ends with an n. My name is Ben. This is no good.
            printf("%s contains an n.\n",cur_str);
        } else {
            //This time print the string
            fprintf(ndict, "%s\n", cur_str);
        }
    }
    fclose(ndict);
    readf.close();
    printf("Done!\n");
    return 0;
}
