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
    FILE *writeover;
    writeover = fopen("NewData.txt","w");
    fclose(writeover);
    char * pch;
    long int numb;
    string word;
    fstream dict ("odict");
    fstream in ("BigData.txt");
    fstream out ("newData.txt");
    while (in >> word) {
        dict.seekg(0); //Bring dict to the beginning!
        //cut out the empty strings!
        pch=strtok((char*)word.c_str(),"0123456789");
        while (pch != NULL) {
            numb++;
            if (numb%500000==0)
                printf("At word: %ld\n",numb);
//            out << pch;
//            out << "\n";
            pch = strtok(NULL, "0123456789");
        }
    }
    in.close();
    return 0;
}
