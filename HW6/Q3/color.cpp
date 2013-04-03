#include "Graph.h"
#include "Graph3.cpp"
#include "baseclass.cpp"
#include <stdlib.h>

int Graph::color() {

    return 0;
}

int main() {
    srand(5);
    Graph graph;
    string liststring;
    int n=4;
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
    int c=2;
    int inbase[n];
    Base b (inbase,2,n);
    b.clear();
    b.setBase(c);
    b.print();
    for (int i=0; i<3991; i++) {
        b++;
    }
    b.print();
    return 0;

}
