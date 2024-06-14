#include "BSTree.h"

//Implemantations of BST
template<typename T>
BSTree<T>::BSTree()
{
    root = nullptr;
    returnitemafteradd = false;
}

template<typename T>
bool BSTree<T>::searchitem(string data)
{
    if (nullptr != searchitem(root, data))
        return true;
    else
        return false;
}
template<typename T>
T* BSTree<T>::searchitem(Node* localRoot, string itemsearching)
{
    if (localRoot == nullptr)
    {
        return nullptr;
    }

    if (localRoot->item == itemsearching)
    {
        cout << localRoot->item << endl;
    }

    else if (localRoot->item < itemsearching)
    {
        return searchitem(localRoot->right, itemsearching);
    }
    else
    {
        return searchitem(localRoot->left, itemsearching);
    }

    return searchitem(localRoot->left, itemsearching);
}

template<typename T>
bool BSTree<T>::addItem(T* newItem)
{
    root = addItem(root, newItem);
    return returnitemafteradd;
}
template<typename T>
typename BSTree<T>::template Node* BSTree<T>::addItem(Node* localRoot, T* newItem)
{
    if (localRoot == nullptr)
    {
        returnitemafteradd = true;
        return new Node(*newItem);
    }
    else if (localRoot->item == *newItem)
    {
        returnitemafteradd = false;
        return localRoot;
    }
    else if (localRoot->item < *newItem)
    {
        localRoot->right = addItem(localRoot->right, newItem);
        return localRoot;
    }
    else
    {
        localRoot->left = addItem(localRoot->left, newItem);
        return localRoot;
    }
}

template<typename T>
T* BSTree<T>::deleteItem(T* newItem)
{
    root = deleteItem(root, newItem);
    return deleteditemafteremove;
}
template<typename T>
typename BSTree<T>:: template Node* BSTree<T>::deleteItem(Node* localRoot, T* RemoveItem)
{
    if (localRoot == nullptr)
    {
        deleteditemafteremove = nullptr;
        return localRoot;
    }
    if (localRoot->item == *RemoveItem)
    {
        deleteditemafteremove = &(localRoot->item);
        if (localRoot->left == nullptr)
        {
            Node* temper = localRoot->right;
            delete localRoot;
            return temper;
        }
        else if (localRoot->right == nullptr)
        {

            Node* temper = localRoot->left;
            delete localRoot;
            return temper;
        }

        else
        {
            if (localRoot->left->right == nullptr)
            {
                localRoot->item = localRoot->left->item;
                Node* temper = localRoot->left->left;
                delete localRoot->left;
                localRoot->left = temper;
                return localRoot;
            }
            else
            {
                localRoot->item = FLN(localRoot->left);
                return localRoot;
            }
        }
    }
    else if (localRoot->item > *RemoveItem)
    {
        localRoot->left = deleteItem(localRoot->left, RemoveItem);
        return localRoot;
    }

    else if (localRoot->item < *RemoveItem)
    {
        localRoot->right = deleteItem(localRoot->right, RemoveItem);
        return localRoot;
    }
    return localRoot;
}

template<typename T>
T BSTree<T>::FLN(Node* localRoot)
{
    if (localRoot->right->right != nullptr)
        return FLN(localRoot->right);
    else
    {
        T Valuetoreturn = localRoot->right->item;
        Node* temper = localRoot->right->left;
        delete localRoot->right;
        localRoot->right = temper;
        return Valuetoreturn;

    }
}

template<typename T>
int BSTree<T>::heightoftree()
{
    return height_of_tree(root);
}
template<typename T>
int BSTree<T>::heightoftree(BSTree<T>::Node* localRoot)
{
    if (localRoot == nullptr)
        return 0;
    // cout<<localRoot->item<<endl;
    int Lheight = heightoftree(localRoot->left);
    int Rheight = heightoftree(localRoot->right);
    return 1 + max(Lheight, Rheight);
}

template<typename T>
int BSTree<T>::heightoftreeRight()
{
    return heightoftree(root->right);
}
template<typename T>
int BSTree<T>::heightoftreeLeft()
{
    return heightoftree(root->left);
}

//implementations of AVL