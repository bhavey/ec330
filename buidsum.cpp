using namespace std;
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <limits>
#include <vector>

int buildsum() {
    int sum;
    FILE *readf;
    readf = fopen("Buid.txt","r");
    string cur_str;
    while (readf >> cur_str);
        if ((cur_str+1)==1) {
            printf("buid: %s\n",cur_str);
            sum++;
        }
    }
    return sum;
}
