#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "string"
#include "RedBlack.h"
using namespace std;

//pseudocode taken from http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap14.htm 14.2 LEFT-ROTATE section
void RedBlack::leftRotate(Node *node) {
    Node* y = node->right;
    node->right = y->left;
    if(y->left != nullptr){
        y->left->parent = node;
    }
    y->parent = node->parent;
    if(node->parent == nullptr){
        root = y;
    }else if(node == node->parent->left){
        node->parent->left = y;
    } else{
        node->parent->right = y;
    }
    y->left = node;
    node->parent = y;
}

//adapted from left rotate
void RedBlack::rightRotate(Node *node) {
    Node* y = node->left;
    node->left = y->right;
    if(y->right != nullptr){
        y->right->parent = node;
    }
    y->parent = node->parent;
    if(node->parent == nullptr){
        root = y;
    }else if(node == node->parent->right){
        node->parent->right = y;
    } else{
        node->parent->left = y;
    }
    y->right = node;
    node->parent = y;
}

Node* RedBlack::RBTreeGetGrandparent(Node* node){
    return node->parent->parent;
}
Node* RedBlack::RBTreeGetUncle(Node* node){
    if(node->parent->parent != nullptr){
        //go to grandparent look left & right if it doesnt match then thats the uncle
        if(node->parent->parent->left != node->parent){
            return node->parent->parent->left;
        } else{
            return node->parent->parent->right;
        }
    }
    return nullptr;
}

//pseudocode taken from balanced trees lecture slides
void RedBlack::balance(Node *node) {
    if(node->parent == nullptr) {
        node->color = "black";
        return;
    }
    if(node->parent->color == "black"){
        return ;
    }
    Node* parent = node->parent;
    Node* gp = RBTreeGetGrandparent(node);
    Node* uncle = RBTreeGetUncle(node);

    if(uncle != nullptr && uncle->color == "red"){
        parent->color = uncle->color = "black";
        gp->color = "red";
        balance(gp);
        return;
    }
    if(node == parent->right && parent == gp->left){
        leftRotate(parent);
        node = parent;
        parent = node->parent;
    }else if(node == parent->left && parent == gp->right){
        rightRotate(parent);
        node = parent;
        parent = node->parent;
    }

    parent->color = "black";
    gp->color = "red";

    if(node == parent->left){
        rightRotate(gp);
    }else{
        leftRotate(gp);
    }

}

//http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap13.htm section 13.3 for TREE INSERT pseudocode
Node* RedBlack::insert(vector<string> genre, string title, string description,int pages, string author, double rating) {
    //insertion into a BST cited from AVL project
    Node* node = new Node(genre,title,description,pages, author,rating);
    Node* y = nullptr;
    Node* x = this->root;
    while(x!= nullptr){
        y = x;
        if(node->pages < x->pages){
            x = x->left;
        } else{
            x = x->right;
        }
    }
    node->parent = y;
    if(y == nullptr){
        root = node;
    } else if(node->pages < y->pages){
        y->left = node;
    } else{
        y->right = node;
    }

    balance(node);
}
