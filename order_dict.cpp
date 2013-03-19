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
    regex_t re;
    regmatch_t match;
    FILE *odict;
    odict = fopen("odict","w");
    fclose(odict);
    char cur_str[25];
    char prev_str[25];
    for (int i=1; i<25; i++) {
        ifstream readf ("ndict");
        FILE *odict;
        odict = fopen("odict","a");
        while (readf >> cur_str) {
            if (strlen(cur_str)!=i) {
                continue;
            }
            fprintf(odict, "%s ", cur_str);
        }
        fclose(odict);
        readf.close();
    }
    //NOTE: This file was confirmed to have all lower case values by running in a bash shell the following:
    //cat ndict | grep [[:upper:]]*, it didn't print anything so there were no upper case letters.
    //There are no repeats, because running cat ndict | tr " " "\n" | uniq -d gave no result, so there were no
    //repeating lines.
    printf("Done!\n");
    return 0;
}
