#ifndef BSTREE_H
#define BSTREE_H

#include<string>
#include<vector>
#include<iostream>
#include<fstream>

using namespace std;

template<class T>
class BSTree
{
public:

    struct Node
    {
        Node* right;
        Node* left;
        T item;

        Node(T new_item)
        {
            item = new_item;
            right = nullptr;
            left = nullptr;
        }

        Node()
        {
            right = nullptr;
            left = nullptr;
        }

    };

    BSTree();

    bool addItem(T* newItem);
    T* deleteItem(T* RemoveItem);
    bool  searchitem(string findpartialstring);

    int heightoftree();
    int heightoftreeRight();
    int heightoftreeLeft();

private:
    Node* root;

    ofstream drawtreefile;
    ofstream inorderfile;
    ofstream preorderfile;

    bool returnitemafteradd;
    T* deleteditemafteremove;

    Node* addItem(Node* localRoot, T* newItem);
    Node* deleteItem(Node* localRoot, T* RemoveItem);

    vector<bool> pathofthenode;

    T FLN(Node* localRoot);

    int heightoftree(Node* localRoot);
    T* searchitem(Node* localRoot, string itemsearching);

    void drawtree(Node* localRoot, vector<bool> step, int subtreeside);
    void printpreorderTraversal(Node* localRoot);
    void printinorderTraversal(Node* localRoot);
};
#endif
