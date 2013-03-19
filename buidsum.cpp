using namespace std;
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <limits>
#include <vector>
#include <string>

int main() {
    int sum;
    ifstream readf ("Buid.txt");
    char cur_str[10];
    while (readf >> cur_str) {
        if (cur_str[1]+cur_str[2]+cur_str[3]+cur_str[4]+cur_str[5]+cur_str[6]+cur_str[7]+cur_str[8]-384
            ==24) {
            printf("buid: %s\n",cur_str);
            sum++;
        }
    }
    readf.close();
    printf("Sum: %d\n",sum);
    printf("Done!\n");
    return sum;
}
//            printf("value: %d\n",
  //              cur_str[1]+cur_str[2]+cur_str[3]+cur_str[4]+cur_str[5]+cur_str[6]+cur_str[7]+cur_str[8]);
