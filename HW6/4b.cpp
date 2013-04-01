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
    sprintf(fstring1,"http://algorithmics.bu.edu/ec330_scripts/homeworks/hw6/hw6.php?seed=%d",PHI+i);
    sprintf(fstring2,"hw6.php?seed=%d",PHI+i);
    char *wgetCmd[] = {"wget",fstring1,0};
    fstream in;
    int pipes[2];
    pipe(pipes);

    if ((pid = fork()) < 0) printf("Error Forking.\n");
    else if (pid == 0) {
//        dup2(pipes[0],0);
        close(pipes[1]);
        close(pipes[0]);
        execvp(wgetCmd[0],wgetCmd);
    } else {
        int status;
        pid_t childPid;
        childPid = wait(&status);
    }
    in.open(fstring2, fstream::in);

    while (in >> entry) { //Find relevant entries and put them in the vetors
        cur_total=0;
        printf("%s\n",entry.c_str());
        for (int j=0; j<entry.length(); j++)
            if (entry[j]=='_')
                cur_total++;
        total+=cur_total;
    }
    printf("Total characters in crossword: %d\n",total);
    in.close();
    remove(fstring2);
    return 0;
}
