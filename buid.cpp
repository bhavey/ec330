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
    int numb=1;

    long long pos=8063854;
    long long new_pos;

    pid_t pid;
    for (int i = 0; i<100; i++) {
        if ((pid = fork()) == 0) { //child process
            fstream in ("BigData.txt");
            in.ignore(pos, '\0');
            printf("pos: %lld\n",pos);


            while (in >> word) {
                numb++;
                if (numb%10000==0) {
                    new_pos = in.tellg();
                    printf("\n\n");
                    printf("pos: %lld\n",pos);
                    printf("new_pos: %lld\n",new_pos);
                    printf("numb: %d\n",numb);
                }
                if (numb%100000==0) {
                    new_pos = in.tellg();
                    in.close();
                    printf("pos: %lld\n",pos);
                    break;
                }
                p=word.c_str();
                regcomp(&re, "U[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]", REG_EXTENDED);
                while(regexec(&re, p, 1, &match, 0) == 0) {
//            printf("%.*s\n", (int)(match.rm_eo - match.rm_so), &p[match.rm_so]);
                    p += match.rm_eo;
                }
            }
        } else { //parent process.
            pid_t childPid;
            int status;
            childPid = wait(&status); //wait for the child to finish.
        }
            pos = new_pos;
            printf("new_pos: %lld\n",new_pos);
            printf("fuck you: %lld\n",pos);
            in.close();
            words.clear();
            word.clear();
    }

    return 0;
}
