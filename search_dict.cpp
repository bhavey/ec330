using namespace std;
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <regex.h>
#include <pthread.h>

#define BIG_WORDS 67469012 //number of words in the BigData.txt files
#define TOT_ITR 5000000 //Amount of words to search through every process iteration
#define THREAD_TOT (int)(BIG_WORDS/TOT_ITR + 1) //rounded amount of total threads
#define BUF_SIZE

typedef struct {
    int id; //thread id
    long long pos;
    int numb;
    int flagvar;
    int matches;
} parm;

void *thread_run(void *arg);

int main() {
    long int total_matches=0;
    int n, flagvar;
    pthread_t *threads;
    pthread_attr_t attr;
    parm *p;
    //Initialize our thread stuff.
    threads=(pthread_t *)malloc(THREAD_TOT*sizeof(*threads));
    pthread_attr_init(&attr);
    p=(parm *)malloc(sizeof(parm)*n);

    FILE *writeover;
    //Write over Filepos.txt
    writeover = fopen("Filepos222.txt","w");
    fputs("0\n0",writeover);
    fclose(writeover);

    //Create the threads fo real now!
    for (int i=0; i<THREAD_TOT; i++) {
        if (i==0) {
            p[0].pos=0;
            p[0].numb=1;
        } else {
            p[i].pos=p[i-1].pos;
            p[i].numb=p[i-1].numb;
        }
        p[i].matches=0;
        p[i].id=i;
        p[i].flagvar=0;
        pthread_create(&threads[i], &attr, thread_run, (void *)(p+i));
        while (p[i].flagvar==0);
        total_matches+=p[i].matches;
        printf("At thread %d, there are %ld total matches.\n",i,total_matches);
    }

    for (int i=0; i<THREAD_TOT; i++)
        pthread_join(threads[i],NULL);

    //Free the parameters in each of the threads
    free(p);
}

void *thread_run(void *arg) {
    parm *p = (parm*)arg;
    p->matches=0;
    printf("Thread %d is running.\n", p->id);
    //open the dictionary and BigData.txt
    fstream big ("BigData.txt");
    fstream dict ("ndict");
    if ((!big) || (!dict)) {
        printf("Error opening either BigData.txt or ndict.\n");
        p->flagvar=1;
        return (NULL);
    }
    string word;
    //Skip to your current position in BigData
    big.ignore(p->pos, '\0');
    while ( big >> word ) {
        p->numb++;
        if (p->numb%TOT_ITR==0) {
            p->pos = big.tellg();
            printf("Finished process %d\n",p->id);

            break;
        }
    }
    p->flagvar=1;
    return (NULL);
}
