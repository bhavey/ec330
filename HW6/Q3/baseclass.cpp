#include <set>
#include <map>
#include <sstream>
#include <string>
#include <iterator>
#include <iostream>
#include <vector>

using namespace std;
//Creates a Base.
class Base {
public:
    Base () {};
    Base (int* a,int b);
    Base operator ++(int);
    void setBase(int);
    void setContents(int*);
    void print();
    void clearBase();
    bool checkEmpty();

private:
    int *contents;
    int base;
};

Base::Base (int *a, int b) {
    contents=a;
    base=b;
    for (int i=0; i<sizeof(contents)/sizeof(int); i++)
        if (contents[i]>=base)
            contents[i]=0;
}

Base Base::operator++(int a) {
    for (int i=0; i<sizeof(contents)/sizeof(int); i++) {
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
void Base::setContents(int *in) {
    for (int i=0; i<sizeof(contents)/sizeof(int); i++) {
        if (contents[i]>=base) {
            printf("Please set contents to base %d\n",base);
            return;
        }
    }
    contents=in;
}

void Base::print() {
    printf("base: %d\n",base);
//    printf("print: %d\n",this->contents[0]);
//    for (int i=0; i<sizeof(contents)/sizeof(int); i++)
//        printf("%d%c",contents[i],(i==(sizeof(contents)/sizeof(int)-1)?'\n':','));
    return;
}

void Base::clearBase() {
    for (int i=0; i<sizeof(contents)/sizeof(int); i++)
        contents[i]=0;
    return;
}

bool Base::checkEmpty() {
    for (int i=0; i<sizeof(contents)/sizeof(int); i++)
        if (contents[i] != 0)
            return false;
    return true;
}

int main() {
    int colormap[4]={1,1,1,3};
    Base b2 (colormap,3);
    b2.print();
    b2.setContents(colormap);
    return 0;
}
