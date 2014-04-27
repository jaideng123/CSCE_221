#include <cstdlib>
#include <iostream>
#include <stdexcept>
using namespace std;
template<class T> class DoublyLinkedList; // class declaration

// list node
template<class T> class DListNode {
private: T obj;
  DListNode<T> *prev, *next;
  friend class DoublyLinkedList<T>;
public:
  DListNode(T e=T(), DListNode<T> *p = NULL, DListNode<T> *n = NULL)
    : obj(e), prev(p), next(n) {}
  T getElem() const { return obj; }
  DListNode<T> * getNext() const { return next; }
  DListNode<T> * getPrev() const { return prev; }
};

// doubly linked list
template<class T> class DoublyLinkedList {
protected: DListNode<T> header, trailer;
public:
  DoublyLinkedList() : header(T()), trailer(T()) // constructor
  { header.next = &trailer; trailer.prev = &header; }
  DoublyLinkedList( DoublyLinkedList<T>& dll); // copy constructor
  ~DoublyLinkedList(); // destructor
  DoublyLinkedList& operator=(DoublyLinkedList<T>& dll); // assignment operator
  // return the pointer to the first node
  DListNode<T> *getFirst() const { return header.next; } 
  // return the pointer to the trailer
  const DListNode<T> *getAfterLast() const { return &trailer; }
  // return if the list is empty
  bool isEmpty() const { return header.next == &trailer; }
  T first() const; // return the first object
  T last() const; // return the last object
  void insertFirst(T newobj); // insert to the first of the list
  T removeFirst(); // remove the first node
  void insertLast(T newobj); // insert to the last of the list
  T removeLast(); // remove the last node
  void copy(DoublyLinkedList& dll1);//copies list
  void emptyList(DoublyLinkedList& dll);
};

// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};
//empty_list function
template<class T> void DoublyLinkedList<T>::emptyList(DoublyLinkedList<T>& dll){
	while(!dll.isEmpty()){
	dll.removeLast();
	}
	return;
}
//copy function
//copies from dll1
template<class T> void DoublyLinkedList<T>::copy(DoublyLinkedList<T>& dll1){
	emptyList(*this);//empties current list
	T temp = T();
	DListNode<T>* tempPtr = dll1.getFirst();//start at 1 past header
	while(tempPtr->getNext() != NULL){//make sure im not on the trailer node
	temp = tempPtr->getElem();//get elem
	insertLast(temp);//copy
	tempPtr = tempPtr->getNext();
  }
	return;
}
// copy constructor
template<class T> DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>& dll)
{
  header=T();
  trailer=T();
  header.next = &trailer; 
  trailer.prev = &header;
  copy(dll);
}
// assignment operator
template<class T> DoublyLinkedList<T>& DoublyLinkedList<T>::operator=( DoublyLinkedList<T>& dll)
{
  header=T();
  trailer=T();
  header.next = &trailer; trailer.prev = &header;
  copy(dll);
}
// insert the object to the first of the linked list
template<class T> void DoublyLinkedList<T>::insertFirst(T newobj)
{ 
  DListNode<T> *newNode = new DListNode<T>(newobj, &header, header.next);
  header.next->prev = newNode;
  header.next = newNode;
}
// insert the object to the last of the linked list
template<class T> void DoublyLinkedList<T>::insertLast(T newobj)
{
  DListNode<T> *newNode = new DListNode<T>(newobj, trailer.prev,&trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}
// remove the first object of the list
template<class T> T DoublyLinkedList<T>::removeFirst()
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode<T> *node = header.next;
  node->next->prev = &header;
  header.next = node->next;
  T obj = node->obj;
  delete node;
  return obj;
}
// remove the last object of the list
template<class T> T DoublyLinkedList<T>::removeLast()
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode<T> *node = trailer.prev;
  node->prev->next = &trailer;
  trailer.prev = node->prev;
  T obj = node->obj;
  delete node;
  return obj;
}
// destructor
template<class T> DoublyLinkedList<T>::~DoublyLinkedList()
{
  DListNode<T> *prev_node, *node = header.next;
  while (node != &trailer) {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
}
// return the first object
template<class T> T DoublyLinkedList<T>::first() const
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return header.next->obj;
}
// return the last object
template<class T> T DoublyLinkedList<T>::last() const
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return trailer.prev->obj;
}
// return the list length
template<class T> int DoublyLinkedListLength(DoublyLinkedList<T>& dll) {
  DListNode<T> *current = dll.getFirst();
  int count = 0;
  while(current != dll.getAfterLast()) {
    count++;
    current = current->getNext(); //iterate
  }
  return count;
}
// output operator
template<class T> ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll) {
	T temp = T();
	DListNode<T>* tempPtr = dll.getFirst();
	//basically a modified version of copy
	while(tempPtr->getNext() != NULL){
	temp = tempPtr->getElem();
	out<<temp<<",";
	tempPtr = tempPtr->getNext();
  }
  
  return out;
}
