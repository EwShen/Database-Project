//Ewan Shen
//2396486
//ewshen@chapman.edu
//Michael Smith
//2396546
//michsmith@chapman.edu
//CPSC-350-01
//PA5
//doublely linked list class
//details a doublely linked list, which contains nodes connected through pointers pointing in both directions

#ifndef DBL_LIST_H
#define DBL_LIST_H

#include "ListNode.h"
#include <fstream>

template <typename T>
class DblList{
public:
  DblList();
  virtual ~DblList();

  //vanilla
  bool isEmpty();
  int getSize();
  bool contains(T value);
  void log(ostream& outStream);
  //add
  void addFront(T data);
  void addBack(T data);
  void add(int pos, T data);

  //remove
  T removeFront();
  T removeBack();
  T remove(int pos);
  void removeElement(T data);

  //accessor
  T get(int pos);

protected:
  ListNode<T>* m_front;
  ListNode<T>* m_back;
  int m_size;

};

template <typename T>
DblList<T>::DblList(){
  m_front = NULL;
  m_back = NULL;
  m_size = 0;
}

template <typename T>
DblList<T>::~DblList(){
  //todo - free memory
  delete m_front;
  delete m_back;
  m_size = 0;
}

template <typename T>
bool DblList<T>::isEmpty(){
  return (m_size==0);
}

template <typename T>
int DblList<T>::getSize(){
  return m_size;
}

template <typename T>
bool DblList<T>::contains(T value){
  bool found = false;
  ListNode<T>* current = m_front;
  while(current != NULL){
    if(current->m_data == value){
      found = true;
      break;
    }
    current = current->m_next;
  }
  return found;
}

template <typename T>
T DblList<T>::get(int pos){
  //do our error checking
  int cPos = 0;
  ListNode<T>* current = m_front;
  while(cPos!=pos){
    current = current->m_next;
    ++cPos;
  }
  return current->m_data;
}

template <typename T>
void DblList<T>::addFront(T data){
  ListNode<T>* newNode = new ListNode<T>(data);
  if(!isEmpty()){
    m_front->m_prev = newNode;
    newNode->m_next = m_front;

  } else{
    m_back = newNode;
  }
  m_front = newNode;
  ++m_size;
}

template <typename T>
void DblList<T>::addBack(T data){
  ListNode<T>* newNode = new ListNode<T>(data);
  if(!isEmpty()){
    m_back->m_next = newNode;
    newNode->m_prev = m_back;
  } else{
    m_front = newNode;
  }
  m_back = newNode;
  ++m_size;
}

template <typename T>
void DblList<T>::add(int pos, T data){
  //do some checking for weirdness
  if(isEmpty()){ //empty
    addFront(data);
  } else if(pos == 0){ //add at front
    addFront(data);
  } else if (pos >= m_size){ //adding at back
    addBack(data);
  } else{ //adding in middle
    ListNode<T>* newNode = new ListNode<T>(data);
    int cPos = 0;
    ListNode<T>* current= m_front;
    while(cPos != pos){
      current = current->m_next;
      ++cPos;
    }
    current->m_prev->m_next = newNode;
    newNode->m_prev = current->m_prev;
    current->m_prev = newNode;
    newNode->m_next = current;
    ++m_size;
  }
}

template <typename T>
T DblList<T>::removeFront(){
  //handle if list is empty
  T data;
  data = m_front->m_data;
  if(m_size==1){
    delete m_front;
    m_front = NULL;
    m_back = NULL;
  } else{
    ListNode<T>* currFront = m_front;
    m_front = m_front->m_next;
    m_front->m_prev = NULL;
    currFront->m_next = NULL;
    delete currFront;
  }
  --m_size;
  return data;
}

template <typename T>
T DblList<T>::removeBack(){
  //handle if list is empty
  T data;
  data = m_back->m_data;
  if(m_size==1){
    delete m_back;
    m_front = NULL;
    m_back = NULL;
  } else{
    ListNode<T>* currBack = m_back;
    m_back = m_back->m_prev;
    m_back->m_next = NULL;
    currBack->m_prev = NULL;
    delete currBack;
  }
  --m_size;
  return data;
}

template <typename T>
T DblList<T>::remove(int pos){
  //check if empty and throw exception
  T data;
  if(pos <= 0){
    data = removeFront();
  } else if(pos >= m_size-1){
    data = removeBack();
  } else{ //somewhere in middle
    ListNode<T>* current = m_front;
    int cPos = 0;
    while(cPos != pos){
      current = current->m_next;
      ++cPos;
    }
    data = current->m_data;
    current->m_prev->m_next = current->m_next;
    current->m_next->m_prev = current->m_prev;
    current->m_prev = NULL;
    current->m_next = NULL;
    delete current;
    --m_size;
  }

  return data;
}


template <typename T>
void DblList<T>::log(ostream& outStream){
  ListNode<T>* current = m_front;
  while(current!=NULL){
    outStream << current->m_data << endl;
    current = current->m_next;
  }
}

//removeElement method is added to the provided doublely linked list class
//removeElement removes an element from a doublely linked list given a specific data
template <typename T>
void DblList<T>::removeElement(T data){
  ListNode<T>* current = m_front;
  int cpos = 0;
  while(current->m_data != data && current != NULL){
    if(current == m_back){
      return;
    }
    current = current->m_next;
    cpos++;
  }
  remove(cpos);
  return;
}
#endif
