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
    srand(time(NULL));
    Graph graph;
    for (int i = 0; i < 16; i++)
        graph.addVertex(0);
    for (int i = 0; i < 2; i++) {
        graph.addEdge(make_pair(0+8*i,1+8*i));
        graph.addEdge(make_pair(0+8*i,3+8*i));
        graph.addEdge(make_pair(0+8*i,4+8*i));
        graph.addEdge(make_pair(1+8*i,2+8*i));
        graph.addEdge(make_pair(1+8*i,5+8*i));
        graph.addEdge(make_pair(2+8*i,3+8*i));
        graph.addEdge(make_pair(2+8*i,6+8*i));
        graph.addEdge(make_pair(3+8*i,7+8*i));
        graph.addEdge(make_pair(4+8*i,5+8*i));
        graph.addEdge(make_pair(4+8*i,7+8*i));
        graph.addEdge(make_pair(5+8*i,6+8*i));
        graph.addEdge(make_pair(6+8*i,7+8*i));
    }
    for (int i=0; i<8; i++)
        graph.addEdge(make_pair(i,i+8));

    string teststr;
    printf("Give random vertices #: ");
    cin >> teststr;
    int size = atoi(teststr.c_str());
    string liststring;

//COMMENT ME OUT TO MAKE A HYPER CUBE!!!
    graph=graph.generateRandom(size);
    liststring=graph.modprint();

    printf("Mod: %s\n",liststring.c_str());
    int n = 0;

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
            n++;
        }
        else {
            rowvec.push_back(atoi(pch));
        }
        pch=strtok(NULL," ");
    }
    printf("size: %d\n",n);

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

    printf("Unordered Incidence Matrix: \n");
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++)
            printf("%d ",adjmat[i][j]);
        printf("\n");
    }

    if (n<=0) {
        printf("Chromatic number is 0.\n");
        return 0;
    } else if (n==1) {
        printf("Chromatic number is 1.\n");
        return 0;
    } else if (n==2) {
        if ((adjmat[0][0]==1)||(adjmat[0][1]==1))
            printf("Chromatic number is 2.\n");
        else
            printf("Chromatic number is 1.\n");
        return 0;
    }


    printf("\n");
    //Now we have our unordered adjacency matrix! Test all possible color schemes!
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
    timeval first;
    gettimeofday(&first, NULL);
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
                            time1=(float)(end.tv_sec-start.tv_sec);

                            cur_perc+=this_perc;
                            float perc_remaining=100/cur_perc;
                            printf("%%%.2f complete. Estimated remaining time: %.1f\n",//avgtime,
                            cur_perc,
                            100/cur_perc*time1 - time1);
                            printf("Percentage: %.2f\n", cur_perc);
                            cur_b3=b.at(2);
                        }
            }
            if (flagvar) {
                b.print();
                printf("Chromatic number: %d\n",b.getBase());
                gettimeofday(&end, NULL);
                time1=(float)(end.tv_sec-first.tv_sec);
                printf("Took %.0f seconds to calculate.\n",time1);
                return 0;
            }

        }
        printf("Chromatic number failed for %d\n",b.getBase());
    }
    printf("Chromatic number is %d\n",n);
    return 0;

}
