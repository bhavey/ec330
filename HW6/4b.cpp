#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <sys/types.h>
#include <stdlib.h>
using namespace std;

#define PHI 74
int main() {
    int cur_total;
    int total;
    pid_t pid;
    char fstring1[1000];
    char fstring2[1000];
    int i=0;
    string entry;
    for (int i=0; i<101; i++) {
        sprintf(fstring1,"http://algorithmics.bu.edu/ec330_scripts/homeworks/hw6/hw6.php?seed=%d",PHI+i);
        sprintf(fstring2,"hw6.php?seed=%d",PHI+i);
        char *wgetCmd[] = {"wget","-q",fstring1,0};
        fstream in;
        int pipes[2];
        pipe(pipes);

        if ((pid = fork()) < 0) printf("Error Forking.\n");
        else if (pid == 0) {
            execvp(wgetCmd[0],wgetCmd);
        } else {
            int status;
            pid_t childPid;
            childPid = wait(&status);
        }
        in.open(fstring2, fstream::in);

        printf("Reading board: %d\n",i);
        while (in >> entry) { //Find the underscores.
            cur_total=0;
            for (int j=0; j<entry.length(); j++)
                if (entry[j]=='_')
                    cur_total++;
            total+=cur_total;
        }
        in.close();
        remove(fstring2);
    }
    printf("Total characters in crossword: %d\n",total);
        return 0;
}
