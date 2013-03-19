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
    ifstream readf ("ndict");
    regex_t re;
    regmatch_t match;
    FILE *ndict;
    ndict = fopen("ndict1","w");
    char cur_str[25];
    while (readf >> cur_str) {
            fprintf(ndict, "%s ", cur_str);
    }
    fclose(ndict);
    readf.close();
    printf("Done!\n");
    return 0;
}
