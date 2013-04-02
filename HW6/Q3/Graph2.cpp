#include "Graph.h"
#include <iostream>

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
    Graph graph;
    return graph;
}

int main() {

/*Creates the following graph:
0<->1->2
|
\->3
with the coloring:
1<->2->1
|
\->5
*/

    Graph graph;
    string gstring;
    graph.addVertex(1); //Makes vertex 0 of color 1.
    graph.addVertex(2); //Makes vertex 1 of color 2.
    graph.addVertex(1);
    graph.addVertex(5);
    directedEdge Edge1(0,1); //0->1
    directedEdge Edge2(1,0); //1->0
    directedEdge Edge3(1,2); //1->2
    directedEdge Edge4(0,3); //0->3
    printf("Color of vertex 0: %d\n", graph.getColor(0));
    printf("Color of vertex 1: %d\n", graph.getColor(1));
    graph.addEdge(Edge1);
    graph.addEdge(Edge2);
    graph.addEdge(Edge3);
    graph.addEdge(Edge4);
    if (graph.isEdge(Edge1))
        printf("0->1 is an edge.\n");
    else
        printf("0->1 is not an edge.\n");
    gstring=graph.print();
    printf("%s\n",gstring.c_str());
    return 0;
}
