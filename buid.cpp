using namespace std;
#include <iostream>
#include <math.h>
#include <regex.h>
#include <stdio.h>
#include <limits>

int main() {
    regex_t re;
    char file[] = "hello777world99yew U46525972 I8909do23!";
    const char *p = file;
    regmatch_t match;

    if(regcomp(&re, "[[:space:]]U[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][[:space:]]", REG_EXTENDED) != 0) {
        printf("No results found.\n");
        return -1;
    }

    while(regexec(&re, p, 1, &match, 0) == 0) {
        printf("%.*s\n", (int)(match.rm_eo - match.rm_so), &p[match.rm_so]);
        p += match.rm_eo;
    }

    return 0;
}
