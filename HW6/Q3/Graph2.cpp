#include "Graph.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

Graph::Graph() {
    set<int> vertices;
    set< directedEdge > edges;
    map<int,int> colors;
};

int Graph::addVertex(int color) { //Create a vertex of color. Return ID of the vertex
    vertexIterator it = vertices.end(); //Go to the last item in the set;
    if (vertices.size()==0) { //brand new! Initialize!
        vertices.insert(0);
        colors[0] = color;
        return 0;
    } else {
        vertices.insert(*(--it)+1); //Add the new vertex!
        int vertID=*(++it); //Get the ID of the new vertex.
        colors[vertID] = color; //Apply the color to the new ID.
        return vertID; //return the new vertex ID
    }
}

void Graph::addEdge(directedEdge newEdge) {
    directedEdge tmpEdge = newEdge;
    vertexIterator vEnd = vertices.end();
    vertexIterator it1 = vertices.find(newEdge.first);
    vertexIterator it2 = vertices.find(newEdge.second);
    if ((it1==vEnd)||(it2==vEnd)) { //Missing vertex. Break.
        printf("One or both vertices isn't initialized.\n");
    } else { //Add the set to the end of the edges list.
        edges.insert(newEdge); //insert the directed edge.
    }
    return;
}

int Graph::getColor(int vertex) {
    return colors[vertex];
}

bool Graph::isEdge(directedEdge newEdge) {
    set< directedEdge >::iterator it;
    int nE1, nE2, it1, it2;
    nE1=newEdge.first;
    nE2=newEdge.second;
    for (it = edges.begin(); it != edges.end(); ++it) {
        if ( ((*it).first==nE1) && ((*it).second==nE2) ) {
            return true;
        }
    }
    return false;
}

string Graph::print() {
	stringstream result;
	for (vertexIterator vert1=vertices.begin(); vert1 != vertices.end(); vert1++) {
		result << *vert1 << "[" << getColor(*vert1) << "]: ";
		for (vertexIterator vert2 = vertices.begin(); vert2 != vertices.end(); vert2++)
			if (isEdge (directedEdge(*vert1, *vert2)))
				result << *vert2 << " ";
		result << endl;
	}
		return result.str();
}

Graph Graph::generateRandom(int num) {
    srand (time(NULL));
    Graph graph;
    for (int i=0; i<num; i++) {
        graph.addVertex(rand()%num);
    }
    directedEdge Ed1(0,0);
    for (int i=0; i<num; i++) {
        for (int j=0; j<num; j++) {
            if (rand()%2<1) { //%50 odds!
                Ed1.first=i;
                Ed1.second=j;
                graph.addEdge(Ed1);
            }
        }
    }
    return graph;
}

int main() {
//Creates a random graph.
    Graph graph;
    string gstring;
    graph=graph.generateRandom(5);
    gstring=graph.print();
    printf("%s\n",gstring.c_str());
    return 0;
}
