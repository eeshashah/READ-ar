//valid unique book checker
//printing
//height
//nodes
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "string"
#include "RedBlack.h"
using namespace std;


Node* RedBlack::insert(Node* root, string genre, string title, string review, int length, string timePeriod, double rating) {
 //insertion into a BST cited from AVL project
    if (root == nullptr)
        return new Node( genre,  title,  review,  length,  timePeriod,  rating);
      //if node is root change color to black
    else if (length < (root->length))
        root->left = insert(root->left, genre, title, review, length, timePeriod, rating);
    else
        root->right = insert(root->right, genre, title, review, length, timePeriod, rating);
}

void RedBlack::insertHelper(string genre, string title, string review, int length, string timePeriod, double rating) {
  insert(genre, title, review, length, timePeriod, rating);
}

Node* RedBlack::balance(Node* node){
  if(node->parent == null){
    node->red = false;
    return;
  }
  if(node->parent->red == false){
    return;
  }
  Node* parent = node->parent;
  Node* gp = RBTreeGetGrandparent(node);
  Node* uncle = RBTreeGetUncle(node);
  if(uncle != nullptr && uncle->color == red){
    parent->color = uncle->color = black;
    gp->color = red;
    balance(gp);
    return;
  }
  if(node == parent->right && parent == gp->left){
    
  }
}

Node* RedBlack::RBTreeGetGrandparent(Node* node){
  return node->parent->parent;
}
Node* RedBlack::RBTreeGetUncle(Node* node){
  return node->parent->parent;
}