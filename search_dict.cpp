using namespace std;
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <regex.h>
#include <pthread.h>

#define BIG_WORDS 67469012 //number of words in the BigData.txt files
#define TOT_ITR 500000 //Amount of words to search through every process iteration
#define THREAD_TOT (int)(BIG_WORDS/TOT_ITR + 1) //rounded amount of total threads
#define BUF_SIZE

typedef struct {
    int id; //thread id
    ifstream in;
    FILE *out;
    long long pos;
    int number;
} parm;

void *thread_run(void *arg);

int main() {
    int n, flagvar;
    pthread_t *threads;
    pthread_attr_t attr;
    parm *p;
    threads=(pthread_t *)malloc(136*sizeof(*threads));
}

void *thread_run(void *arg) {
    parm *p = (parm*)arg;
    printf("%d thread is running.\n", p->id);
    return (NULL);
}
