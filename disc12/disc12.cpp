#include "Graph.h"
#include "Graph3.cpp"
#include "baseclass.cpp"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

int n = 0;
//These are the voyages of starship USS Enterprise:
//Commander Riker is taken hostage by a Borg cube in deep space.
//He ends up wooing Seven of Nine, Tertiary Adjunct of Unimatrix Zero-One.
//At the same time Georgi and Data accidentally turn Diana into a man
//in a failed experiment to make the warp cores faster. Captain Picard
//is a little too comfortable with this.


//Returns the lowest ordered vertice in a graph.
//Only considers a vertex if there is a "1" number at the beginning of the row.
//This is a flag to consider if its still in the graph.
int findLowestOrder(bool **adjmat) {
    int vert, tmpvert, lowestVert;
    lowestVert=999999; //Set lowest vertex to infinity.
    for (int i=0; i<n; i++) {
        tmpvert=0;
        if (adjmat[i][0]==0) {
            continue; //No longer a valid vertex, as it has been removed. Continue on.
        }
        for (int j=0; j<n; j++) {
            if (adjmat[i][j+1]==1)
                tmpvert++;
        }
        printf("Order for %d: %d\n",i,tmpvert);
        if (tmpvert<lowestVert) {
            lowestVert=tmpvert;
            vert=i;
            printf("in there at %d\n",i);
        } 
    }
    return vert;
}

//Remove a particular vertex from an adjacency matrix.
void removeVertFromAdjacency(int vert, bool **&adjmat) {
    adjmat[vert][0]=0; //Set the flag to zero, showing the vertex has been removed.
    for (int i=0; i<n; i++) {
        adjmat[i][vert+1]=0;
    }
    return;
}

vector<int> indepSet(int vert, bool **adjmat) {
    vector<int> returnVec;
    bool **tmpmat = new bool*[n+1];
    for (int i=0; i<n; i++)
        tmpmat[i] = new bool[n];    bool flagvar=1;
    tmpmat = adjmat;
    while (flagvar) {
        flagvar=0;
        //Find the lowest ordered vertex
        int lowestVert=findLowestOrder(tmpmat);
        returnVec.push_back(lowestVert);
        //Remove the vertex and its neighbors.
        for (int i=0; i<n; i++) {
            if (tmpmat[lowestVert][i+1]==1)
                removeVertFromAdjacency(i+1,tmpmat); //Remove the neighbors!
        }
        removeVertFromAdjacency(lowestVert,tmpmat); //Remove the lowest ordered vertex.
        for (int i=0; i<n; i++) {
            if (tmpmat[i][0]==1)
                flagvar=1; //Repeat if there is at least one remaining vertex.
        }
    }
    return returnVec;
}

int Graph::color() {
//********************************************************************************
//Greedy Graph Coloring: Basic idea is that you go through the graph, finding
//the largest independent set of vertices possible at any given iteration. Each of
//these vertices is colored a new color. At this point remove the independent set
//from the graph and then repeat the process until you have all vertices colored.

//Optimal substructure: The optimal substructure is the largest possible set of
//indepented vertices. This can be found by locating the lowest ordered vertex and
//then placing this in the set and removing the vertex and its neighbors from the graph.
//Continue until the entire graph is empty. Number of independent sets required to empty
//the graph is the color # of the graph.

//Worst possible graph would be an incomplete bipartite graph with at least one vertex
//having fewer edges (not less then or equal) then the others. Since the algorithm only
//considers the lowest ordered vertex when first picking in a set, it will pick one
//of the lower ordered vertices first. This ends up with at least one vertex not getting
//colored the first time around. It'll require way more iterations this way then necessary.

    string liststring;
    liststring=modprint();

    char *gstring=(char*)liststring.c_str();
    int gsize=liststring.length();
    int colorsize;

    vector<vector<int> > tempvec;
    vector<int> rowvec;
    char *pch;
    pch=strtok(gstring," ");
    int i=0;
    //Put adjacency list in adjacency matrix
    //strtok spaces + new lines
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
    map<int,int> neighbor_number;
    int *vert_ord = new int[n];

    //initialize the adjacency matrix
    bool **adjmat = new bool*[n];
    for (int i=0; i<n; i++)
        adjmat[i] = new bool[n+1];
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            adjmat[i][j+1]=0;
    for (int i=0; i<n; i++)
        adjmat[i][0]=1; //Still a valid vertex! The first index is a flag variable,
    //which shows whether or not a node is in a vertex

    bool **tmpmat = new bool*[n+1];
    for (int i=0; i<n; i++)
        tmpmat[i] = new bool[n];

    //Fill the unordered adjacency matrix.
    for (int i=0; i<tempvec.size(); i++) {
        for (int j=0; j<tempvec.at(i).size(); j++) {
            adjmat[i][tempvec.at(i).at(j)+1]=1;
            adjmat[tempvec.at(i).at(j)][i+1]=1;
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (adjmat[i][j]==1) 
                neighbor_number[i]++;
        }
    }
    printf("Unordered Incidence Matrix: \n");
    for (int i=0; i<n; i++) {
        for (int j=0; j<n+1; j++)
            printf("%d ",adjmat[i][j]);
        printf("\n");
    }
    tmpmat=adjmat;
    removeVertFromAdjacency(1, tmpmat);
    removeVertFromAdjacency(3, tmpmat);
    removeVertFromAdjacency(4, tmpmat);
    int lowOrd;
    lowOrd=findLowestOrder(tmpmat);
    printf("LOWEST ORDER: %d\n",lowOrd);
    printf("Unordered Incidence Matrix, w.o. vertices 1/3: \n");
    for (int i=0; i<n; i++) {
        for (int j=0; j<n+1; j++)
            printf("%d ",tmpmat[i][j]);
        printf("\n");
    }
    return colorsize;
}

int main() {

    srand(time(NULL));
    Graph graph;
/*
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
*/
    for (int i=0; i<6; i++)
        graph.addVertex(0);


    //Create a complete Bipartite graph.
    for (int i=0; i<3; i++) {
        for (int j=3; j<6; j++) {
            graph.addEdge(make_pair(i,j));
            graph.addEdge(make_pair(j,i));
        }
    }

    string teststr;
    //printf("Give random vertices #: ");
  //  cin >> teststr;
    //int size = atoi(teststr.c_str());
    string liststring;

//COMMENT ME OUT TO MAKE A HYPER CUBE!!!
//    graph=graph.generateRandom(size);
    liststring=graph.modprint();

    printf("Mod: %s\n",liststring.c_str());
    int chrome=graph.color();
    printf("Chromatic number: %d\n",chrome);
    return 0;
}
