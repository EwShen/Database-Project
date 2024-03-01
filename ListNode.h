//Ewan Shen
//2396486
//ewshen@chapman.edu
//Michael Smith
//2396546
//michsmith@chapman.edu
//CPSC-350-01
//PA5
//details the list node object, which is implemented in the doublely linked list class
//list nodes are interconnected between pointers which point the opposite directions in the doublely linked list class

#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <cstdlib>
#include <iostream>
using namespace std;

//header section
template <typename T>
class ListNode{
public:
  ListNode(T data);
  virtual ~ListNode();
  template <typename S>
  friend class DblList;

private:
  // list node has pointers to previous and next node
  ListNode<T>* m_next;
  ListNode<T>* m_prev;
  T m_data;
};

//constructor
template <typename T>
ListNode<T>::ListNode(T data){
  m_data = data;
  m_next = NULL;
  m_prev = NULL;
}

//destructor
template <typename T>
ListNode<T>::~ListNode(){
  m_next = NULL;
  m_prev = NULL;
}

#endif
