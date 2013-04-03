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
    int n=5;
    printf("size: %d\n",n);
    graph=graph.generateRandom(5);
    liststring=graph.modprint();

    char *gstring=(char*)liststring.c_str();
    int gsize=liststring.length();

    vector<vector<int> > tempvec;
    vector<int> rowvec;
    printf("in:\n%s\n",gstring);
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
    printf("now testing!\n");
    for (int i=0; i<tempvec.size(); i++) {
        printf("%d: ",i);
        for (int j=0; j<tempvec.at(i).size(); j++) {
            printf("%d ",tempvec.at(i).at(j));
        }
        printf("\n");
    }
    int inbase[n];
    Base b2 (inbase,2,n);
    b2.clear();
    b2.setBase(5);
    b2.print();
    for (int i=0; i<3991; i++) {
        b2++;
    }
    b2.print();
    return 0;

}
