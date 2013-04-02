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
    void operator ++(int);
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
void Base::operator++(int a) {
    //Base b = *this;
    for (int i=size-1; i>=0; i--) {
        contents[i]++;
        //printf("Base[%d]: %d, base: %d.\n",i,contents[i],base);
        if (contents[i]>=base) {
    //        printf("A.\n");
            contents[i]=0;
        } else {
  //         printf("B.\n");
           return;
        }
    }
//    printf("made it here...\n");
//    return (Base)*this;
    return;
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
