#include <cstdlib>
#include <iostream>
using namespace std;
class DoublyLinkedList; // class declaration

// list node
class DListNode {
private: int obj;
  DListNode *prev, *next;
  friend class DoublyLinkedList;
public:
  DListNode(int e=0, DListNode *p = NULL, DListNode *n = NULL)
    : obj(e), prev(p), next(n) {}
  int getElem() const { return obj; }
  DListNode * getNext() const { return next; }
  DListNode * getPrev() const { return prev; }
};

// doubly linked list
class DoublyLinkedList {
protected: DListNode header, trailer;
public:
  DoublyLinkedList() : header(0), trailer(0) // constructor
  { header.next = &trailer; trailer.prev = &header; }
  DoublyLinkedList( DoublyLinkedList& dll); // copy constructor
  ~DoublyLinkedList(); // destructor
  DoublyLinkedList& operator=(DoublyLinkedList& dll); // assignment operator
  // return the pointer to the first node
  DListNode *getFirst() const { return header.next; } 
  // return the pointer to the trailer
  const DListNode *getAfterLast() const { return &trailer; }
  // return if the list is empty
  bool isEmpty() const { return header.next == &trailer; }
  int first() const; // return the first object
  int last() const; // return the last object
  void insertFirst(int newobj); // insert to the first of the list
  int removeFirst(); // remove the first node
  void insertLast(int newobj); // insert to the last of the list
  int removeLast(); // remove the last node
  void copy(DoublyLinkedList& dll1);//copies list
  void emptyList(DoublyLinkedList& dll);
};
// output operator
ostream& operator<<(ostream& out, const DoublyLinkedList& dll);