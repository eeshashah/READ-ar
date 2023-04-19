#pragma once
#include <string>
#include <vector>
using namespace std;

struct Node {
    bool red;
    string genre;
    string title;
    string review;
    int length;
    string timePeriod;
    double rating;
    Node *left;
    Node *right;
    Node *parent;
    Node (string genre, string title, string review, int length, string timePeriod, double rating): red(true), genre(genre),       title(title), review(review), length(length), timePeriod(timePeriod), rating(rating), left(nullptr), right(nullptr), parent(nullptr){};
  };

class RedBlack {
public:
  Node* insert(Node* root, string genre, string title, string review,int length, string timePeriod, double rating);
  void insertHelper(string genre, string title, string review,int length, string timePeriod, double rating);
  Node* balance(Node* node);
  Node* RBTreeGetGrandparent(Node* node);
  Node* RBTreeGetParent(Node* node);
  void print();
  Node* rightRotate();
  Node* leftRotate();
  Node* rightLeftRotate();
  Node* leftRightRotate();
  void uniqueBookTitle();
  void BFS();
  void DFS();
  Node* root;
};