#include "Graph.h"
#include <iostream>

using namespace std;

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
