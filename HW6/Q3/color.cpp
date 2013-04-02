#include "Graph.h"
#include "Graph3.cpp"
#include "baseclass.cpp"
#include <stdlib.h>

int Graph::color() {

    return 0;
}

int main() {
    srand(1);
    Graph graph;
    string gstring;
    graph=graph.generateRandom(3);
    gstring=graph.print();
    printf("%s\n",gstring.c_str());
    printf("now testing!\n");

    int inbase[3]={0,0,0};
    Base b2 (inbase,2,3);
    printf("initialized: ");
    printf("cleared: ");
    b2.print();
    printf("Incremented: \n");
    b2.print();
    for (int i=0; i<16; i++) {
        printf("1\n");
        b2++;
        printf("2\n");
        b2.print();
        printf("3\n");
    }
    printf("Set to base three, incremented: \n");
    b2.clear();
    b2.setBase(3);
    b2.print();
    for (int i=0; i<81; i++) {
        b2++;
        b2.print();
    }
    printf("Here maybe?\n");
    printf("really...\n");
    return 0;

}
