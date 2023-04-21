#pragma once
#include <string>
#include <vector>
using namespace std;

struct Node {
    string color;
    string author;
    vector<string> genre;
    string title;
    string description;
    int pages;
    double rating;
    Node *left;
    Node *right;
    Node *parent;
    Node (vector<string> genre, string title, string description, int pages, string author, double rating): color("red"), genre(genre), title(title),
    author(author), pages(pages), description(description), rating(rating), left(nullptr), right(nullptr), parent(nullptr){};
};

class RedBlack {
    Node* insert(vector<string> genre, string title, string description,int pages, string author, double rating);
public:
    Node* root;
    void balance(Node* node);
    Node* RBTreeGetGrandparent(Node* node);
    Node* RBTreeGetUncle(Node* node);
    void print();
    void rightRotate(Node* node);
    void leftRotate(Node* node);
    void uniqueBookTitle(Node* node);
    void BFS();
    void DFS();
    RedBlack():root(){};
};
