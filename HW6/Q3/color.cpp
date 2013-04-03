#include "Graph.h"
#include "Graph3.cpp"
#include "baseclass.cpp"
#include <stdlib.h>
#include <math.h>

int Graph::color() {

    return 0;
}

int main() {
    srand(5);
    Graph graph;
    string liststring;
    int n=5;
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
    printf("Adjacency vectors:\n");
    for (int i=0; i<tempvec.size(); i++) {
        printf("%d: ",i);
        for (int j=0; j<tempvec.at(i).size(); j++) {
            adjmat[i][tempvec.at(i).at(j)]=1;
            adjmat[tempvec.at(i).at(j)][i]=1;
            printf("%d ",tempvec.at(i).at(j));
        }
        printf("\n");
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("%d ",adjmat[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    //Now we have our unordered adjacency matrix! Test all possible color schemes!
//    int c=3;
    int inbase[n];
    int loop_index;
    Base b (inbase,2,n);
    for (int c=2; c<n; c++) {
        loop_index=pow(c,n); //go up this high!
        b.clear();
        b.setBase(c);
        int cur_col;
        int flagvar=1;
        int j=0,k=0;
        for (int i=0; i<loop_index; i++) {
            flagvar=1;
            b++;
            for (j=0; (j<n)&&flagvar; j++) {
                cur_col=b.at(j);
                for (k=0; (k<n)&&flagvar; k++) {
                    if ((adjmat[j][k])&&(j!=k)) { //Edge detected!
                        if (cur_col==b.at(k)) {//Matching colors... :/ don't work!
                            //printf("Breaking...\n");
                            flagvar=0;
                            continue;
                        }
                    }
                }
            }
            if (flagvar) {
                b.print();
                printf("Here without continuing!\n");
                return 0;
            }
        }
    }
    return 0;

}
