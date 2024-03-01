//Ewan Shen
//2396486
//ewshen@chapman.edu
//Michael Smith
//2396546
//michsmith@chapman.edu
//CPSC-350-01
//PA5
//details the tree node
//tree nodes are interconnected in BSTs and specifically the Scapegoat tree in this project

#ifndef TREE_NODE_H
#define TREE_NODE_H


#include <cstdlib>
#include <iostream>

template <typename T>
class TreeNode{
public:
  TreeNode(T d);
  virtual ~TreeNode();
  T getData();
  template <typename S>
  friend class BST;
  template <typename R>
  friend class ScapegoatST;
private:
  T m_data;
  TreeNode<T>* m_left;
  TreeNode<T>* m_right;
};

template <typename T>
TreeNode<T>::TreeNode(T d){
  m_data = d;
  m_left = NULL;
  m_right = NULL;
}

template <typename T>
TreeNode<T>::~TreeNode(){
  if(m_left != NULL){
    delete m_left;
  }
  if(m_right != NULL){
    delete m_right;
  }
}

template <typename T>
T TreeNode<T>::getData(){
  return m_data;
}

#endif
