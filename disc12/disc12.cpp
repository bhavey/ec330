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
vector<int> indepSet(int vert, bool **adjmat) {
    printf("Unordered Incidence Matrix: \n");
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++)
            printf("%d ",adjmat[i][j]);
        printf("\n");
    }
    vector<int> outVec;
    return outVec;
}

//Returns the lowest ordered vertice in a graph.
int findLowestOrder(bool **adjmat) {
    int vert, tmpvert, lowestVert;
    lowestVert=999999; //Set lowest vertex to infinity.
    for (int i=0; i<n; i++) {
        tmpvert=0;
        for (int j=0; j<n; j++) {
            if (adjmat[i][j]==1)
                tmpvert++;
        }
        if (tmpvert<lowestVert) {
            lowestVert=tmpvert;
            vert=i;
        } 
    }
    return vert;
}

//Remove a 
void removeVertFromAdjacency(bool **adjmat) {
    return;
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
//Continue until the entire graph is empty.

//Worst possible graph would be a complete bipartite graph, because the
//optimal substructure would then pick every graph as a relative "root",
//At this point since they are all the same it would simply iterate through
//picking a new color for every vertex.

//The greedy coloring algorithm first sets every vertex color to -1, then sorts the
//vertices by their degree and then place them into a sorted array. Iterate through
//this array and apply a color for each node that isn't taken by its neighbors. This
//is best done as an adjacency matrix.

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
//    bool adjmat[n][n];
    bool **adjmat = new bool*[n];
    for (int i=0; i<n; i++)
        adjmat[i] = new bool[n];

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
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (adjmat[i][j]==1) 
                neighbor_number[i]++;
        }
    }
    printf("Unordered Incidence Matrix: \n");
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++)
            printf("%d ",adjmat[i][j]);
        printf("\n");
    }

    return colorsize;
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
