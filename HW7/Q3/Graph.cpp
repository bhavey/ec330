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

Graph Graph::Boruvka() {
//Personal implementation of the Boruvka minimum span tree
/* Boruvka-MST()
1. Graph OutGraph
2. array[size(V)] Touched={0,0,...0,0}
3. int Check_Done = V-1
4. array[0]=1 //Touch the first vertice!
5. while (true)
6.     Tmp_Done=Check_Done
7.     for i vertices in V
8.         if possible, Select lowest adjacent vertex j that is untouched
9.             array[j]=1
10.            Check_Done--
11.            addEdge to OutGraph
12.    if Tmp_Done==Check_Done
13.        break
14. Return Outgraph
*/
    Graph Out;
    int vert_size=vertices.size();
    int *Touched = new int[vert_size];
    for (int i=1; i<=vert_size; i++) {
        Out.addVertex(i);
        Touched[i-1]=0;
    }
    int vert2=Out.vertices.size();
    int doneCheck=vertices.size();
    int tmpCheck=0;
    int edge1, edge2;
    int lastminprice;
    int newminprice;
    Touched[0]=true;
    while (doneCheck!=tmpCheck) {
        tmpCheck=doneCheck;
        for (vertexIterator vert1=vertices.begin(); vert1 != vertices.end(); vert1++) {
            lastminprice=999999999;
            for (vertexIterator vert2 = vertices.begin(); vert2 != vertices.end(); vert2++) {
                if (isEdge (directedEdge(*vert1, *vert2, NULL))) {
                    //Check the edge!
                    if (!Touched[*vert2]) { //It's untouched!
                        newminprice=getPrice(directedEdge(*vert1,*vert2,NULL));
                        if (newminprice<lastminprice) {
                            lastminprice=newminprice;
                            edge1=*vert1;
                            edge2=*vert2;
                            doneCheck--;
                        }
                    }
                }
            }
            if (lastminprice!=999999999) {
                //Would you pay 1 billion dollars to go to a city?
                //Didn't think so.
                Touched[edge2]=lastminprice;
                Out.addEdge(directedEdge(edge1,edge2,lastminprice));
            }
        }
    }
    //If there is a lower bidder 
    delete[] Touched;
    return Out;
}

Graph Graph::Dijkstra(int root) {
/*
 1  function Dijkstra(Graph, source):
 2      for each vertex v in Graph:                                // Initializations
 3          dist[v] := infinity ;                                  // Unknown distance function from 
 4                                                                 // source to v
 5          previous[v] := undefined ;                             // Previous node in optimal path
 6      end for                                                    // from source
 7      
 8      dist[source] := 0 ;                                        // Distance from source to source
 9      Q := the set of all nodes in Graph ;                       // All nodes in the graph are
10                                                                 // unoptimized - thus are in Q
11      while Q is not empty:                                      // The main loop
12          u := vertex in Q with smallest distance in dist[] ;    // Source node in first case
13          remove u from Q ;
14          if dist[u] = infinity:
15              break ;                                            // all remaining vertices are
16          end if                                                 // inaccessible from source
17          
18          for each neighbor v of u:                              // where v has not yet been 
19                                                                 // removed from Q.
20              alt := dist[u] + dist_between(u, v) ;
21              if alt < dist[v]:                                  // Relax (u,v,a)
22                  dist[v] := alt ;
23                  previous[v] := u ;
24                  decrease-key v in Q;                           // Reorder v in the Queue
25              end if
26          end for
27      end while
28  return dist;
*/
    Graph Out;
    int vert_size=vertices.size();
    int *dist = new int[vert_size];
    int *previous = new int[vert_size];
    for (int i=0; i<vert_size; i++) {
        dist[i]=999999999;
        previous[i]=NULL;
    }
    dist[root] = 0;
    set<int> Q = this->vertices;
    Out.vertices=Q;
    string poop;
    poop=Out.print();
    printf("Out:\n");
    printf("%s\n",poop.c_str());
    int u;
    int cur_u;
    int smallest_dist;
    int alt;
    while (Q.size() != 0) { //While Q is not empty.
        smallest_dist=1000000000;
        for (vertexIterator q=Q.begin(); q!=Q.end(); q++) {
            //Find the smallest distance u in Q.
            if (dist[*q]<smallest_dist) {
                smallest_dist=dist[*q];
                u=*q;
            }
        }
        Q.erase(u); //Remove u from Q.
        if (dist[u]>=999999999) { //break if dist[u]>inf
            break;
        }
        for (vertexIterator v=vertices.begin(); v!=vertices.end(); v++) {
            if (isEdge(directedEdge(u,*v,NULL))) { //For each neighbor v of u.
                alt = dist[u] + getPrice(directedEdge(u,*v,NULL));
                if (alt < dist[*v]) {
                    dist[*v] = alt;
                    previous[*v] = u;
                }
            }
        }
    }
    printf("Dist: ");
    for (int i=0; i<vert_size; i++) 
        printf("%d ",dist[i]);
    printf("\n");
    delete [] dist;
    delete [] previous;
    return Out;
}


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
    if ((it1==vEnd) || (it2==vEnd)) { //Missing vertex. Break.
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

int Graph::getPrice(directedEdge newEdge) { //Same as isEdge function, but return the weight
    set< directedEdge >::iterator it;
    int nE1, nE2, it1, it2;
    nE1=newEdge.first;
    nE2=newEdge.second;
    for (it = edges.begin(); it != edges.end(); ++it) {
        if ( ((*it).first==nE1) && ((*it).second==nE2) ) {
            return (*it).third;
        }
    }
    return -1;
}

string Graph::print() {
    int price;
	stringstream result;
	for (vertexIterator vert1=vertices.begin(); vert1 != vertices.end(); vert1++) {
		result << *vert1 << "[" << getColor(*vert1) << "]:  ";
		for (vertexIterator vert2 = vertices.begin(); vert2 != vertices.end(); vert2++)
			if (isEdge (directedEdge(*vert1, *vert2, NULL))) {
                price=getPrice(directedEdge(*vert1, *vert2, NULL));
                result << *vert2 << "(" << price << "), " ;
            }
		result << std::endl;
	}
		return result.str();
}

Graph Graph::generateRandom(int num) {
    srand (time(NULL));
    Graph graph;
    for (int i=0; i<num; i++) {
        graph.addVertex(rand()%num);
    }
    directedEdge Ed1(0,0,NULL);
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
//    graph=graph.generateRandom(5);
    directedEdge Edge(0,1,3);
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);
    graph.addVertex(5);
    graph.addEdge(directedEdge(0,1,3));
    graph.addEdge(directedEdge(0,2,40));
    graph.addEdge(directedEdge(2,1,5));
    graph.addEdge(directedEdge(1,2,6));
    graph.addEdge(directedEdge(1,3,20));
    graph.addEdge(directedEdge(3,0,10));
    graph.addEdge(directedEdge(3,4,2)); 
    graph.addEdge(directedEdge(4,2,1)); 


    gstring=graph.print();
    printf("%s",gstring.c_str());
    printf("0 to 1: %d,   2 to 1: %d,   1 to 0: %d\n",graph.getPrice(directedEdge(0,1,NULL)),
        graph.getPrice(directedEdge(2,1,NULL)),graph.getPrice(directedEdge(1,0,NULL)));
  //  printf("The output of MST:\n");
    //Graph graph2;
 //   graph2=graph.Boruvka();
   // gstring=graph2.print();
    //printf("Min span tree of graph:\n");
    //printf("%s",gstring.c_str());
    graph.Dijkstra(1);
    return 0;
}