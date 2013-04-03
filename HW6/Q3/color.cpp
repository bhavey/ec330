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
    int n=10;
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
    int flagvar=1;
    int flagvar2=1;
    int c=5;
  //  for (int c=2; c<n; c++) {
        flagvar2=1;
        b.setBase(c);
        b.clear();
        b++;
        int cur_col;
        int j=0,k=0;
        printf("checkEmpty: %d\n",b.checkEmpty());
        for (int i=0; (!b.checkEmpty()); i++) {
            flagvar=1;
            for (j=0; (j<n)&&flagvar; j++) {
                cur_col=b.at(j);
                for (k=0; (k<n)&&flagvar; k++) {
                    if ((adjmat[j][k])&&(j!=k)) { //Edge detected!
                        if (cur_col==b.at(k)) {//Matching colors... :/ don't work!
                            flagvar=0;
                            flagvar2=0;
                            b++;
                            continue;
                        }
                    }
                }
            }
            if (flagvar) {
                b.print();
                printf("Chromatic number: %d\n",b.getBase());
                return 0;
            }

        }
        printf("Chromatic number failed for %d\n",b.getBase());
        printf("here?\n");
//    }
    return 0;

}
