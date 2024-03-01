//Ewan Shen
//2396486
//ewshen@chapman.edu
//Michael Smith
//2396546
//michsmith@chapman.edu
//CPSC-350-01
//PA5
//details the scapegoat tree
//the scapegoat tree is coded to rebalance itself once a subtree becomes too heavily weighted

#ifndef SCAPEGOAT_ST_H
#define SCAPEGOAT_ST_H

#include "TreeNode.h"
#include "DblList.h"
#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

template <typename T>
class ScapegoatST{
public:
    ScapegoatST();//constructor
    virtual ~ScapegoatST();//destructor
    void logTree(ofstream& outFile);//logTree method for logging the tree's contents and information
    void insert(T d);//insert data (student or faculty)
    void remove(T d);//remove data (student or faculty)
    T& find(T d);
    bool contains(T d);
    void printInOrder();//print tree in order
    void printPostOrder();//print tree post order
    int getSize();//accessors
    T getMedian();
    T getMin();
    T getMax();
    void rebuildTest();//rebuild tree
    void printTest(TreeNode<T>* n);
    void print();
private:
    //private member variables
    TreeNode<T>* m_root;
    int m_size;
    int m_m;
    //helper methods
    void insertHelper(TreeNode<T>*& subTreeRoot, TreeNode<T>* newNode, DblList<TreeNode<T>*>* path, int& depth);
    bool containsHelper(TreeNode<T>* subTreeRoot, T d);
    void logTreeHelper(TreeNode<T>* subTreeRoot, ofstream& outFile);
    void printInOrderHelper(TreeNode<T>* subTreeRoot);
    void printPostOrderHelper(TreeNode<T>* subTreeRoot);
    T getMinHelper(TreeNode<T>* subTreeRoot);
    T getMaxHelper(TreeNode<T>* subTreeRoot);
    void findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent);//finds the target tree node given a target
    T getSuccessor(TreeNode<T>* node);
    int findSize(TreeNode<T>* subTreeRoot);//finds size of the tree
    void rebuild(TreeNode<T>*& subTreeRoot);//rebuilds the tree after a certain weight of a subtree is reached
    void rebuildHelper(TreeNode<T>* subTreeRoot, T* keyArr, int& i);//helper method for the rebuild method
    TreeNode<T>* buildSubtree(T* keyArr, int size);//builds a subtree
};

template <typename T>
ScapegoatST<T>::ScapegoatST(){//constructor
    m_root = NULL;
    m_size = 0;
}

template <typename T>
ScapegoatST<T>::~ScapegoatST(){//destructor
    if(m_root != NULL){
        delete m_root;
    }
}

template <typename T>
void ScapegoatST<T>::logTree(ofstream& outFile){//logs tree information using the logTreeHelper method
  logTreeHelper(m_root, outFile);
}

template <typename T>
void ScapegoatST<T>::logTreeHelper(TreeNode<T>* subTreeRoot, ofstream& outFile){//descends down the tree and recursively outputs tree node information
  if(subTreeRoot != NULL){
    logTreeHelper(subTreeRoot->m_left, outFile);//logTreeHelper called recursively
    outFile << subTreeRoot->m_data << endl;
    logTreeHelper(subTreeRoot->m_right, outFile);//logTreeHelper called recursively
  }
}

template <typename T>
void ScapegoatST<T>::print(){//print method
    printTest(m_root);
}

template <typename T>
int ScapegoatST<T>::getSize(){//gets the size of the scapegoat tree
    return m_size;
}

template <typename T>
void ScapegoatST<T>::insert(T d){//inserts data into the scapegoat tree
    ++m_size;//increments size
    ++m_m;
    int depth = 0;//initializes depth to 0
    TreeNode<T>* newNode = new TreeNode<T>(d);
    DblList<TreeNode<T>*>* path = new DblList<TreeNode<T>*>();//doublely linked list of tree nodes is initialized
    insertHelper(m_root,newNode, path, depth);
    depth--;//decrements depth
    double maxDepth = log(m_m) / (double)log(3/2.0);//equation to calculate the maximum depth the node can be inserted at
    if(depth > maxDepth){//if the current depth is greater than the maximum depth, the tree is rebuilt if the tempChild divided by tempNode is greater than 2/3
        TreeNode<T>* tempChild = path->removeBack();//tempChild is removed from the back of the doublely linked list
        TreeNode<T>* tempNode = path->removeBack();//tempNode is removed from the back of the doublely linked list
        for(int i = 0; i < depth; i++){
            if(findSize(tempChild) / (double)findSize(tempNode) > 2/3.0){
                TreeNode<T>* GrandParent = path->removeBack();
                bool onRight;
                if(GrandParent->m_right == tempNode){
                    onRight = true;
                }else{
                    onRight = false;
                }
                rebuild(tempNode);//tree is rebuilt to as a result of the tree becoming too heavily weighted on one side
                if(onRight){
                    GrandParent->m_right = tempNode;
                }else{
                    GrandParent->m_left = tempNode;
                }
                break;
            }
            tempChild = tempNode;
            tempNode = path->removeBack();//tempNode is removed from the back of the doublely linked list of the path
        }
    }
}

template <typename T>
void ScapegoatST<T>::insertHelper(TreeNode<T>*& subTreeRoot, TreeNode<T>* newNode, DblList<TreeNode<T>*>* path, int& depth){//insertHelper method recurively travels down the tree to help the insert method
    if(subTreeRoot == NULL){
        subTreeRoot = newNode;
    } else if(newNode->m_data < subTreeRoot->m_data){
        insertHelper(subTreeRoot->m_left,newNode, path, depth);//recursively travels down the tree
    } else{
        insertHelper(subTreeRoot->m_right,newNode, path, depth);//recursively travels down the tree
    }
    path->addFront(subTreeRoot);//the sub tree's root is added to the front of the path doublely linked list
    depth++;//depth is incremented
}


template <typename T>
T& ScapegoatST<T>::find(T d){//find method finds a given object and returns the target data
    TreeNode<T>* target = m_root;
    TreeNode<T>* parent = NULL;
    findTarget(d, target, parent);
    return target->m_data;//returns the target data
}



template <typename T>
bool ScapegoatST<T>::contains(T d){//contains method checks whether a given object is in the scapegoat tree
    return containsHelper(m_root,d);
}

template <typename T>
bool ScapegoatST<T>::containsHelper(TreeNode<T>* subTreeRoot, T d){//containsHelper method recursively travels down the scapegoat tree to see if the given object is in the scapegoat tree
    if(subTreeRoot == NULL){//if the subTree is empty, return NULL
        return false;
    } else if (subTreeRoot->m_data == d){
        return true;//if the data equals the entered parameter object return true
    } else if(d < subTreeRoot->m_data){
        return containsHelper(subTreeRoot->m_left,d);//recursively travel to the children and call the containsHelper method
    } else{
        return containsHelper(subTreeRoot->m_right,d);//recursively travel to the children and call the containsHelper method
    }
}

template <typename T>
void ScapegoatST<T>::printInOrder(){//prints a tree in order
    printInOrderHelper(m_root);
}

template <typename T>
void ScapegoatST<T>::printInOrderHelper(TreeNode<T>* subTreeRoot){//helper method for printing a tree in order
    if(subTreeRoot != NULL){//if the sub tree root is not NULL
        printInOrderHelper(subTreeRoot->m_left);//recursively travels down the tree and prints the tree
        cout << subTreeRoot->m_data << endl;
        printInOrderHelper(subTreeRoot->m_right);//recursively travels down the tree and prints the tree
    }
}

template <typename T>
void ScapegoatST<T>::printPostOrder(){//prints the tree post order
    printPostOrderHelper(m_root);
}

template <typename T>
void ScapegoatST<T>::printPostOrderHelper(TreeNode<T>* subTreeRoot){//helper method for the printPostOrder method
    if(subTreeRoot != NULL){//if the sub tree root is not NULL
        printPostOrderHelper(subTreeRoot->m_left);//recursively travels through the tree and prints the tree
        printPostOrderHelper(subTreeRoot->m_right);//recursively travels through the tree and prints the tree
        cout << subTreeRoot->m_data << endl;
    }
}

template <typename T>
T ScapegoatST<T>::getMedian(){//gets median of the tree
    return m_root->m_data;
}

template <typename T>
T ScapegoatST<T>::getMin(){//gets minimum tree
    return getMinHelper(m_root);
}

template <typename T>
T ScapegoatST<T>::getMax(){//gets maximum of the tree
    return getMaxHelper(m_root);
}

template <typename T>
T ScapegoatST<T>::getMinHelper(TreeNode<T>* subTreeRoot){//helper method for getMin method
    if(subTreeRoot->m_left == NULL){
        return subTreeRoot->m_data;
    } else{
        return getMinHelper(subTreeRoot->m_left);//recursively travels through the tree, updating the minimum everytime a smaller number is encountered
    }
}

template <typename T>
T ScapegoatST<T>::getMaxHelper(TreeNode<T>* subTreeRoot){//helper method for getMax method
    if(subTreeRoot->m_right == NULL){
        return subTreeRoot->m_data;
    } else{
        return getMaxHelper(subTreeRoot->m_right);//recursively travels through the tree, updating the maximum everytime a bigger number is encountered
    }
}

template <typename T>
void ScapegoatST<T>::findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent){//finds the target given a key, target, and parent
    while(target != NULL && target->m_data != key){
        parent = target;
        if(key < target->m_data){
            target = target->m_left;
        } else{
            target = target->m_right;
        }
    }
}

template <typename T>
T ScapegoatST<T>::getSuccessor(TreeNode<T>* node){//node starts at right child, gets the successor of a tree node
    while(node->m_left != NULL){
        node = node->m_left;
    }
    return node->m_data;

}

template <typename T>
void ScapegoatST<T>::remove(T d){//removes a parameter object
    TreeNode<T>* parent = NULL;
    TreeNode<T>* target = NULL;
    target = m_root;
    findTarget(d,target,parent);
    if(target == NULL){ //if the target is not in tree
        return;
    }

    if(target->m_left == NULL && target->m_right == NULL ){ //if the node is a leaf
        if(target == m_root){
            m_root = NULL;
        } else{
            if(target == parent->m_left){
                parent->m_left = NULL;
            } else{
                parent->m_right = NULL;
            }
        }
        m_size--;//decrements the size
        if(m_m > 2*m_size && m_size > 0){
            rebuild(m_root);//rebuild is called if conditions are met for the scapegoat tree
            m_m = m_size;
        }
    } else if(target->m_left != NULL && target->m_right != NULL){ //if the node has two children
        T succValue = getSuccessor(target->m_right);//getSuccessor is called to reach the children
        remove(succValue);//remove method is recursively called to travel down the tree
        target->m_data = succValue;//target equals successor value

    } else{//if the node has one child
        TreeNode<T>* child;
        if(target->m_left != NULL){
            child = target->m_left;
        } else{
            child = target->m_right;
        }
        if(target == m_root){
            m_root = child;
        } else{
            if(target == parent->m_left){
                parent->m_left = child;
            } else{
                parent->m_right = child;
            }
        }
        m_size--;//size is decremented
        if(m_m > 2*m_size){
            rebuild(m_root);//rebuild is called if conditions are met for the scapegoat tree
            m_m = m_size;
        }
    }
}

template <typename T>
void ScapegoatST<T>::rebuildTest(){//rebuildTest method
    rebuild(m_root);//rebuilds the scapegoat tree
}

template <typename T>
void ScapegoatST<T>::printTest(TreeNode<T>* n){//printTest method prints the information of the current node
    if(n->m_left != NULL){
        cout << "the left child of " << n->m_data << " is " << n->m_left->m_data << endl;
        printTest(n->m_left);
    }
    if(n->m_right != NULL){
        cout << "the right child of " << n->m_data << " is " << n->m_right->m_data << endl;
        printTest(n->m_right);
    }
}

template <typename T>
void ScapegoatST<T>::rebuild(TreeNode<T>*& subTreeRoot){//rebuild method for rebuilding the subtree which is called when certain subtree conditions are met
    int size = findSize(subTreeRoot);//size of the scapegoat tree
    T* keyArr = new T[size];
    int i = 0;
    rebuildHelper(subTreeRoot, keyArr, i);//rebuildHelper method is called to help rebuild the scapegoat tree
    subTreeRoot = buildSubtree(keyArr, size);
}


template <typename T>
void ScapegoatST<T>::rebuildHelper(TreeNode<T>* subTreeRoot, T* keyArr, int& i){//helper method for the rebuild method
    if(subTreeRoot != NULL){//if the subtree root is not NULL
        rebuildHelper(subTreeRoot->m_left, keyArr, i);//rebuildHelper is recursively called to travel through the tree
        keyArr[i] = subTreeRoot->m_data;
        i++;
        rebuildHelper(subTreeRoot->m_right, keyArr, i);//rebuildHelper is recursively called to travel through the tree
    }
    return;
}

template <typename T>
TreeNode<T>* ScapegoatST<T>::buildSubtree(T* keyArr, int size){//buildSubtree method for building a subtree
    if(size == 0){
        return NULL;//if the size of the tree is zero, return NULL
    }

    TreeNode<T>* subTreeRoot = new TreeNode<T>(keyArr[size/2]);

    T* L_arr = new T[size/2];
    for(int i = 0; i < size/2; i++){//iterate through the key array
        L_arr[i] = keyArr[i];
    }
    subTreeRoot->m_left = buildSubtree(L_arr, size/2);//buildSubtree is called recursively to travel down the scapegoat tree

    T* R_arr = new T[size/2];
    for(int i = (size/2 + 1); i < size; i++){
        R_arr[i-(size/2 + 1)] = keyArr[i];
    }
    subTreeRoot->m_right = buildSubtree(R_arr, size-(size/2+1));//buildSubtree is called recursively to travel down the scapegoat tree

    return subTreeRoot;//returns the subtree root
}


template <typename T>
int ScapegoatST<T>::findSize(TreeNode<T>* subTreeRoot){//finds the size of the scapegoat tree
    int size = 0;//size is initialized to zero
    if(subTreeRoot != NULL){//if the subtree root is not NULL
        size += 1;//size is incremented
        size += findSize(subTreeRoot->m_left);//findSize is called recursively to travel down the tree
        size += findSize(subTreeRoot->m_right);//findSize is called recursively to travel down the tree
    }
    return size;
}


#endif
