#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "string"
#include "RedBlack.h"
#include <queue>
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
Node* RedBlack::insert(set<string> genre, string title, string description,int pages, string author, string rating, string format) {
    //insertion into a BST cited from AVL project
    Node* node = new Node(genre,title,description,pages, author,rating,format);
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

vector<Node*> RedBlack::DFS(Node* root, string category, int lengthMin, int lengthMax, string format){
    // if item in breadth first search is matching, then add the nodes to an array or something; so you can print them
    // or print them
    cout<< "DFS" <<endl;
    vector<Node*> matches;
    if(root == nullptr){
        return matches;
    }
    //do something
    cout <<"test"<<endl;
    if(root->genre.find(category) != root->genre.end()){
        if(root->pages > lengthMin && root->pages < lengthMax && root->pages != 0) {
            if(root->format == format) {
                matches.push_back(root);
                cout << "Pushing Match: "<< root->title<<endl;
            }
        }
    }
    DFS(root->left, category, lengthMin, lengthMax, format);
    DFS(root->right, category, lengthMin, lengthMax, format);
}

/*vector<Node*> RedBlack::BFS(Node* root, string category, int lengthMin, int lengthMax, string format){
    queue<Node*> queue;
    vector<Node*> matches;
    if(root == nullptr){
        return matches;
    }
    queue.push(root);
    while(!queue.empty()){
        Node* current = queue.front();
        if(root->genre.find(category) != root->genre.end()){
            if(root->pages > lengthMin && root->pages < lengthMax && root->pages != 0) {
                if(root->format == format) {
                    matches.push_back(root);
                    cout << "Pushing Match: "<< root->title<<endl;
                }
            }
        }
        queue.pop();
        if(current->left != nullptr){
            queue.push(queue.front()->left);
        }
        if(current->right != nullptr){
            queue.push(queue.front()->right);
        }
    }

}*/