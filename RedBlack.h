#pragma once
#include <string>
#include <vector>
#include <set>
using namespace std;

struct Node {
    string color;
    string format;
    string author;
    set<string> genre;
    string title;
    string description;
    int pages;
    string rating;
    Node *left;
    Node *right;
    Node *parent;
    Node (set<string> genre, string title, string description, int pages, string author, string rating, string format): color("red"), genre(genre), title(title),
                                                                                                                        author(author), pages(pages), description(description), rating(rating),format(format), left(nullptr), right(nullptr), parent(nullptr){};
};

class RedBlack {
public:
    Node* insert(set<string> genre, string title, string description,int pages, string author, string rating,string format);
    Node* root;
    void balance(Node* node);
    Node* RBTreeGetGrandparent(Node* node);
    Node* RBTreeGetUncle(Node* node);
    void rightRotate(Node* node);
    void leftRotate(Node* node);
    void BFS(Node* root, string category, int lengthMin, int lengthMax, string format, vector<Node*> &matches, int &count, int BFSorDFS);
    void DFS(Node* root, string category, int lengthMin, int lengthMax, string format, vector<Node*> &matches, int &count, int BFSorDFS);
    bool qualityCheck(Node* node, int &count, int BFSorDFS);
    vector<Node*> BFS_holder;
    vector<Node*> DFS_holder;
    void insertIntoHolder(vector<Node*> matches, int BFSorDFS);
    RedBlack():root(){};
};
