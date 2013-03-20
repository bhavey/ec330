//Trie data structure. File contains Trie/Node classes
//Concept taken from http://login2win.blogspot.com/2011/06/c-tries.html
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct X {
    int d;
    char b;
};

using namespace std;

class Node { //Node is a class describing individual nodes in the trie structure.
public:
    //The Node is a particular character in the trie struct. It contains a single character,
    //a marker to denote potential end of words (EOW), and potential children.
    Node() { Data = ' '; Eow = false; } //Start with a space char and no EOW marker
    ~Node() {} //Default destructor
    char data() { return Data; }
    void setData(char c) { Data = c; }
    bool eow() { return Eow; }
    void setEow() { Eow = true; }
    Node* findChild(char c); //Sees if a child is on the Node.
    void appendChild(Node* child) { Child.push_back(child); }
    vector<Node*> children() { return Child; }

private:
    char Data;
    bool Eow;
    vector<Node*> Child;
};

class Trie { //Trie class. Contains a tree of char that represent words that split at different
public:      //characters. Functions are named coherently. (They say what they do)
    Trie();
    ~Trie();
    void addWord(string s);
    bool searchWord(string s);
    void deleteWord(string s);
    X test;
private:
    Node* root;
};

//If a child node belongs to the current node, return the Node* relating to the child,
//Otherwise, return NULL (there is no matching child)
Node* Node::findChild(char c) {
    //Child is a vector of Nodes. Using the std::vector functions the total amount of children
    //belonging to Child can be found using the STL ::size() function
    for ( int i = 0; i < Child.size(); i++ ) { //Loop through ever
        //std::vector::at(n) returns the pointer relating to the nth element of the vector.
        Node* child = Child.at(i);
        if ( child->data() == c ) {
            return child;
        }
    }
    return NULL; //If no children nodes match the char input argument, return NULL.
}

Trie::Trie() { //Create a default node on Trie construction.
    root = new Node();
}

Trie::~Trie() { } //Default Class distructor

void Trie::addWord(string s) { //Adds a word to the Trie tree.
    Node* current = root;

    if ( s.length() == 0 ) { //if s is empty, create Eow flag at the root.
        current->setEow();
        return;
    }

    for ( int i = 0; i < s.length(); i++ ) { //go through the string char by char
        Node* child = current->findChild(s[i]); //See if there is a child.
        if ( child != NULL ) {
            current = child; //If so, go down in the trie to the child node.
        } else { //If no child, create a new node and set the data to the current string char
            Node* nchild = new Node();
            nchild->setData(s[i]);
            current->appendChild(nchild); //append the new child node to the parent node.
            current = nchild; //Go down in the trie to the newly created child node.
        }
        if ( i == s.length() - 1 )
            current->setEow(); //Set the Eow flag at the last node.
    }
}

//Searches through the trie for matching strings.
//Returns true if the word is in the trie, otherwise false.
bool Trie::searchWord(string s) {
    Node* current = root;
    while ( current != NULL ) { //while not strictly necessary, but here as a precaution
        for ( int i = 0; i < s.length(); i++ ) { //loop through entirety of string by char
            Node* child = current->findChild(s[i]); //See if the node has current char in children
            if ( child == NULL ) //findChild returns NULL if there is no relevant child.
                return false;  //Therefore this is false in that case.
            current = child; //Go down to the next child.
        }

        if ( current->eow() ) //Once done check if last node has an eow flag.
            return true;
        else
            return false;
    }
    return false; //Just in case.
}

int main() { //Test program
    //int d, char b, struct test
    Trie* trie = new Trie();
    trie->addWord("Hello");
    trie->addWord("Balloon");
    trie->addWord("Ball");
    trie->test.d = 12; //Modifies an 'x' within 'E'
//    Trie::X out; //This instantiates an 'X' outside of 'E'

    cout << "Trie test: " << trie->test.d << "\n";

    if ( trie->searchWord("Hell") )
        cout << "Found Hell" << endl;

    if ( trie->searchWord("Hello") )
        cout << "Found Hello" << endl;

    if ( trie->searchWord("Helloo") )
        cout << "Found Helloo" << endl;

    if ( trie->searchWord("Ball") )
        cout << "Found Ball" << endl;

    if ( trie->searchWord("Balloon") )
        cout << "Found Balloon" << endl;

    delete trie;
}
