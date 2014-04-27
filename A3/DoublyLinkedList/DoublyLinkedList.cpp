#include "DoublyLinkedList.h"
#include <stdexcept>
// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};
//empty_list function
void DoublyLinkedList::emptyList(DoublyLinkedList& dll){
	while(!dll.isEmpty()){
	dll.removeLast();
	}
	return;
}
//copy function
//copies from dll1 to dll2
void DoublyLinkedList::copy(DoublyLinkedList& dll1){
	emptyList(*this);//empties current list
	int temp = 0;
	DListNode* tempPtr = dll1.getFirst();//start at 1 past header
	while(tempPtr->getNext() != NULL){//make sure im not on the trailer node
	temp = tempPtr->getElem();//get elem
	insertLast(temp);//copy
	tempPtr = tempPtr->getNext();
  }
	return;
}
// copy constructor
DoublyLinkedList::DoublyLinkedList( DoublyLinkedList& dll)
{
  header=0;
  trailer=0;
  header.next = &trailer; trailer.prev = &header;
  copy(dll);
}
// assignment operator
DoublyLinkedList& DoublyLinkedList::operator=( DoublyLinkedList& dll)
{
  header=0;
  trailer=0;
  header.next = &trailer; trailer.prev = &header;
  copy(dll);
}
// insert the object to the first of the linked list
void DoublyLinkedList::insertFirst(int newobj)
{ 
  DListNode *newNode = new DListNode(newobj, &header, header.next);
  header.next->prev = newNode;
  header.next = newNode;
}
// insert the object to the last of the linked list
void DoublyLinkedList::insertLast(int newobj)
{
  DListNode *newNode = new DListNode(newobj, trailer.prev,&trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}
// remove the first object of the list
int DoublyLinkedList::removeFirst()
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode *node = header.next;
  node->next->prev = &header;
  header.next = node->next;
  int obj = node->obj;
  delete node;
  return obj;
}
// remove the last object of the list
int DoublyLinkedList::removeLast()
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode *node = trailer.prev;
  node->prev->next = &trailer;
  trailer.prev = node->prev;
  int obj = node->obj;
  delete node;
  return obj;
}
// destructor
DoublyLinkedList::~DoublyLinkedList()
{
  DListNode *prev_node, *node = header.next;
  while (node != &trailer) {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
}
// return the first object
int DoublyLinkedList::first() const
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return header.next->obj;
}
// return the last object
int DoublyLinkedList::last() const
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return trailer.prev->obj;
}
// return the list length
int DoublyLinkedListLength(DoublyLinkedList& dll) {
  DListNode *current = dll.getFirst();
  int count = 0;
  while(current != dll.getAfterLast()) {
    count++;
    current = current->getNext(); //iterate
  }
  return count;
}
// output operator
ostream& operator<<(ostream& out, const DoublyLinkedList& dll) {
	int temp = 0;
	DListNode* tempPtr = dll.getFirst();
	//basically a modified version of copy
	while(tempPtr->getNext() != NULL){
	temp = tempPtr->getElem();
	out<<temp<<",";
	tempPtr = tempPtr->getNext();
  }
  
  return out;
}
