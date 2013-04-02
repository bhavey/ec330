#include "Graph.h"
#include "Graph3.cpp"
#include "baseclass.cpp"
#include <stdlib.h>

int Graph::color() {

    return 0;
}

int main() {
    srand(4);
    Graph graph;
    string gstring;
    graph=graph.generateRandom(3);
    gstring=graph.print();
    printf("%s\n",gstring.c_str());
    printf("now testing!\n");

    int inbase[4]={0,0,0,0};
    Base b2 (inbase,2,4);
    printf("initialized: ");
    printf("cleared: ");
    b2.print();
    printf("Incremented: \n");
    b2.print();
    for (int i=0; i<15; i++) {
        b2++;
        b2.print();
    }
    printf("Set to base three, incremented: \n");
    b2.clear();
    b2.setBase(5);
    b2.print();
    for (int i=0; i<80; i++) {
        b2++;
        b2.print();
    }
    b2.setBase(93);
    b2.clear();
    for (int i=0; i<3991; i++) {
    b2++;
    }
    b2.print();
    printf("at 2: %d\n",b2.at(2));
    printf("Here maybe?\n");
    printf("really...\n");
    return 0;

}
