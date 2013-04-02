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
    ~Base();
    void setBase(int);
    void setContents(int*, int);
    void print();
    void clear();
    int at(int);
    bool checkEmpty();

private:
    int *contents;
    int base;
    int size;
    int *cont;
};

Base::Base (int *a, int b, int s) {
    base=b;
    size=s;
    int j;
    int *cont;
    cont = new int[size];
    for (int i=0; i<size; i++)
        cont[i]=a[i];
    contents=cont;
    for (int i=0; i<size; i++)
            if (contents[i]>=base) {
                j=i;
                contents[i]=0;
            }
}

Base::~Base() {
    delete cont;
}
Base Base::operator++(int) {
    Base b = *this;
    for (int i=size-1; i>=0; i--) {
        b.contents[i]++;
        if (b.contents[i]==base)
            b.contents[i]=0;
        else
            break;
    }
    return b;
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

int Base::at(int c) {
    if (c>size)
        return -1;
    else
        return contents[c];
}

int main() {
    int colormap[10]={0,1,0,1};
    Base b2 (colormap,2,4);
    printf("initialized: ");
    b2.print();
    b2.clear();
    printf("cleared: ");
    b2.print();
    printf("Contents set: ");
    b2.print();
    b2.clear();
    printf("Cleared/incremented: \n");
    b2.print();
    for (int i=0; i<16; i++) {
        b2++;
        b2.print();
    }
    printf("Set to base three, incremented: \n");
    b2.clear();
    b2.setBase(3);
    b2.print();
    for (int i=0; i<81; i++) {
        b2++;
        b2.print();
    }
    printf("Set to base 12, incremented: \n");
    b2.clear();
    b2.setBase(12);
    b2.print();
    for (int i=0; i<20720; i++) {
        b2++;
        b2.print();
    }
    printf("Contents at 2: %d\n",b2.at(2));
    return 0;
}
