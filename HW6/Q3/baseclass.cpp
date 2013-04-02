#include <set>
#include <map>
#include <sstream>
#include <string>
#include <iterator>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;
//Creates a Base.
class Base {
public:
    Base () {};
    Base (int *a, int b, int s);
    Base operator ++(int);
    void setBase(int);
    void setContents(int*, int);
    void print();
    void clear();
    bool checkEmpty();

private:
    int *contents;
    int base;
    int size;
};

Base::Base (int *a, int b, int s) {
    base=b;
    size=s;
    int j;
    int cont[size];
    for (int i=0; i<size; i++)
        cont[i]=a[i];
    contents=cont;
    for (int i=0; i<size; i++)
            if (contents[i]>=base) {
                j=i;
//THIS HERE****
//                printf("Too big at %d\n",i);
//THE CODE DOESNT WORK WITHOUT THIS PRINT STATEMENT.
                contents[i]=0;
            }
}

Base Base::operator++(int a) {
    for (int i=0; i<size; i++) {
        contents[i]++;
        if (contents[i]==base)
            contents[i]=0;
        else
            break;
    }
}

void Base::setBase(int b) {
    base=b;
}
void Base::setContents(int *in, int s) {
    int cont[size];
    for (int i=0; i<size; i++)
        cont[i]=in[i];
    for (int i=0; i<size; i++) {
        if (cont[i]>=base) {
            cont[i]=0;
        }
    }
    contents=cont;
}

void Base::print() {
    for (int i=0; i<size; i++)
        printf(" %d%c",contents[i],(i==size-1?'\n':','));
    return;
}

void Base::clear() {
    for (int i=0; i<size; i++)
        contents[i]=0;
    return;
}

bool Base::checkEmpty() {
    for (int i=0; i<size; i++)
        if (contents[i] != 0)
            return false;
    return true;
}

int main() {
    int colormap[10]={9,2,0,1,2,1,5,3,1,3};
    Base b2 (colormap,3,10);
    b2.print();

    b2.clear();
    b2.print();
    printf("Colormap: ");
    for (int i=0; i<10; i++)
        printf("%d, ",colormap[i]);
    printf("\n");
    b2.setContents(colormap,10);
    b2.print();
    return 0;
}
