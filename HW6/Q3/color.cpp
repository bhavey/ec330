#include "Graph.h"
#include "Graph3.cpp"
#include "baseclass.cpp"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

int Graph::color() {

    return 0;
}

int main() {
    srand(5);
    Graph graph;
    string liststring;
    int n=16;
    printf("size: %d\n",n);
    graph=graph.generateRandom(n);
    liststring=graph.modprint();

    char *gstring=(char*)liststring.c_str();
    int gsize=liststring.length();

    vector<vector<int> > tempvec;
    vector<int> rowvec;
    char *pch;
    pch=strtok(gstring," ");
    int i=0;
    //Put adjacency list in adjacency matrix
    //strtok spaces, new lines
    while (pch != NULL) {
        if (pch[1]=='!') { //moded graph gives a "! " at every new vertex
            tempvec.push_back(rowvec);
            rowvec.clear();
        }
        else {
            rowvec.push_back(atoi(pch));
        }
        pch=strtok(NULL," ");
    }
    //initialize the adjacency matrix
    bool adjmat[n][n];
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            adjmat[i][j]=0;

    //Fill the unordered adjacency matrix.
    for (int i=0; i<tempvec.size(); i++) {
        for (int j=0; j<tempvec.at(i).size(); j++) {
            adjmat[i][tempvec.at(i).at(j)]=1;
            adjmat[tempvec.at(i).at(j)][i]=1;
        }
    }

    printf("\n");
    //Now we have our unordered adjacency matrix! Test all possible color schemes!
//    int c=3;
    int inbase[n];
    long unsigned int loop_index;
    Base b (inbase,2,n);
    int cur_b3;
    cur_b3=0;
    float cur_perc;
    float this_perc;
    double time1,time2,time3,avgtime;
    int flagvar=1;
    int flagvar2=1;
    int c=0;
    timeval start;
    timeval end;
    for (int c=2; c<n; c++) {
        cur_perc=0;
        this_perc=pow((long)3,c*-1)*100;
        flagvar2=1;
        b.setBase(c);
        b.clear();
        b++;
        gettimeofday(&start, NULL);
        int cur_col;
        unsigned long int j=0,k=0;
            time3=0;
        for (unsigned long int i=0; (!b.checkEmpty()); i++) { //This loop increments through b++.
            flagvar=1;
            for (j=0; (j<n)&&flagvar; j++) {
                cur_col=b.at(j);
                for (k=0; (k<n)&&flagvar; k++) {
                    if ((adjmat[j][k])&&(j!=k)) { //Edge detected!
                        if (cur_col==b.at(k)) {//Matching colors... :/ don't work!
                            flagvar=0;
                            flagvar2=0;
                            if (cur_b3!=b.at(2)) {
                                gettimeofday(&end, NULL);
                                printf("Percentage: %f\n", cur_perc);
                                time1=(float)(end.tv_sec-start.tv_sec);
                                printf("time: %.1f\n",time1);
                                gettimeofday(&start, NULL);
                                cur_perc+=this_perc;
                                cur_b3=b.at(2);

                            }
                            b++;
                            continue;
                        }
                    }
                }
                if (cur_b3!=b.at(2)) {
                            gettimeofday(&end, NULL);
                            if (time3==0) {
                                time1=(float)(end.tv_sec-start.tv_sec);
                                time2=time1;
                                time3=time1;
                            } else {
                                time2=time1;
                                time3=time2;
                                time1=(float)(end.tv_sec-start.tv_sec);
                            }
                            avgtime=(time1+time2+time3)/3;

                            cur_perc+=this_perc;
                            float perc_remaining=(100-cur_perc)/this_perc;
                            printf("%%%.2f complete. Estimated remaining time: %.1f\n",//avgtime,
                            cur_perc,perc_remaining*avgtime);
                            gettimeofday(&start, NULL);
                            printf("Percentage: %.2f\n", cur_perc);
                            cur_b3=b.at(2);
                        }
            }
            if (flagvar) {
                b.print();
                printf("Chromatic number: %d\n",b.getBase());
                return 0;
            }

        }
        printf("Chromatic number failed for %d\n",b.getBase());
    }
    return 0;

}
