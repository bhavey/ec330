#include "Graph.h"
#include <iostream>

using namespace std;

int Graph::addVertex(int color) { //Create a vertex of color. Return ID of the vertex
    vertexIterator it = vertices.end(); //Go to the last item in the set;
    vertices.insert(*(--it)+1); //Add the new vertex!
    int vertID=*(++it); //Get the ID of the new vertex.
    colors[vertID] = color; //Apply the color to the new ID.
    return vertID; //return the new vertex ID
}

void Graph::addEdge(directedEdge newEdge) {
    directedEdge tmpEdge = newEdge;
    vertexIterator vend = vertices.end();
    vertexIterator it1 = vertices.find(newEdge.first);
    vertexIterator it2 = vertices.find(newEdge.second);
    if ((it1==vend)||(it2==vend)) {
        printf("One or both vertices isn't initialized.\n");
        return;
    } else {
    
    }
    return;
}

int Graph::getColor(int vertex) {

    return vertex;
}

bool Graph::isEdge(directedEdge newEdge) {

    return true;
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

int main() {
    printf("Poop!\n");
    return 0;
}
