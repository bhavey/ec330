//Trie data structure. File contains Trie/Node classes
//Concept taken from http://login2win.blogspot.com/2011/06/c-tries.html
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Node { //Node is a class describing individual nodes in the trie structure.
public:
    //The Node is a particular character in the trie struct. It contains a single character,
    //a marker to denote potential end of words (EOW), and potential children.
    Node() { mContent = ' '; mMarker = false; } //Start with a space char and no EOW marker
    ~Node() {} //Default destructor
    char content() { return mContent; }
    void setContent(char c) { mContent = c; }
    bool wordMarker() { return mMarker; }
    void setWordMarker() { mMarker = true; }
    Node* findChild(char c);
    void appendChild(Node* child) { mChildren.push_back(child); }
    vector<Node*> children() { return mChildren; }

private:
    char mContent;
    bool mMarker;
    vector<Node*> mChildren;
};

class Trie {
public:
    Trie();
    ~Trie();
    void addWord(string s);
    bool searchWord(string s);
    void deleteWord(string s);
private:
    Node* root;
};

Node* Node::findChild(char c) {
    for ( int i = 0; i < mChildren.size(); i++ ) {
        Node* tmp = mChildren.at(i);
        if ( tmp->content() == c ) {
            return tmp;
        }
    }
    return NULL;
}

Trie::Trie() {
    root = new Node();
}

Trie::~Trie() { } //Default Class distructor

void Trie::addWord(string s) {
    Node* current = root;

    if ( s.length() == 0 ) {
        current->setWordMarker(); // an empty word
        return;
    }

    for ( int i = 0; i < s.length(); i++ ) {
        Node* child = current->findChild(s[i]);
        if ( child != NULL ) {
            current = child;
        } else {
            Node* tmp = new Node();
            tmp->setContent(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if ( i == s.length() - 1 )
            current->setWordMarker();
    }
}

bool Trie::searchWord(string s) {
    Node* current = root;
    while ( current != NULL ) {
        for ( int i = 0; i < s.length(); i++ ) {
            Node* tmp = current->findChild(s[i]);
            if ( tmp == NULL )
                return false;
            current = tmp;
        }

        if ( current->wordMarker() )
            return true;
        else
            return false;
    }
    return false;
}
