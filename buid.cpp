using namespace std;
#include <iostream>
#include <fstream>
#include <math.h>
#include <regex.h>
#include <stdio.h>
#include <limits>
#include <vector>

int main() {
    regex_t re[100];
    char file[] = "hello777world99yew U46525972 I8909do23!";
    const char *p = file;
    regmatch_t match[100];

    fstream in ("BigData.txt");
    vector<string> words;
    string word;

    if( !in )
        return 0;
    int numb=1;

    long long pos=8063854;
    long long new_pos;
    int cur_pos;

    pid_t pid;
    string tstring;
    for (int i = 0; i<680; i++) {
        if ((pid = fork()) == 0) { //child process
            ifstream opost ("FilePos222.txt");
            getline(opost,tstring);
            pos=strtoll(tstring.c_str(), NULL, 0);
            getline(opost,tstring);
            numb=strtol(tstring.c_str(), NULL, 0);
            opost.close();
            printf("Yo man, here's the position: %lld\n",pos);

            fstream in ("BigData.txt");
            in.ignore(pos, '\0');

            ofstream post;
            ofstream buid ("Buid.txt");

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
                regcomp(&re[i], "U[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]", REG_EXTENDED);
                while(regexec(&re[i], p, 1, &match[i], 0) == 0) {
                    //buid << numb;
//                    fprintf(buid,"%.*s\n", (int)(match.rm_eo - match.rm_so), &p[match.rm_so]);
                    p += match[i].rm_eo;
                }
            }
            printf("Yo biddie, this the pos: %lld\n",pos);
            post.open("Filepos222.txt",ios_base::trunc);
            post << (int)new_pos;
            post << "\n";
            post << numb;
            post.close();
            return 0;
        } else { //parent process.
            pid_t childPid;
            int status;
            childPid=wait(&status);
            printf("new_pos: %lld\n",new_pos);
            pos = new_pos;
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
