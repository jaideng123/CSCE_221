#include <iostream>
using namespace std;

// list node
struct Node {
  int data; // each node holds an integer data
  Node* previous; // pointer to the previous node
  Node* next; // pointer to the next node
  Node(int d=0, Node* prv=NULL, Node* nxt=NULL) : data(d), previous(prv), next(nxt) {}
  Node* get_previous() const { return previous; }
  Node* get_next() const { return next; }
  Node* insert_before(int d); // insert the int before this node
                                // return a pointer to the inserted node
  Node* insert_after(int d); // insert the int after this node
                               // return a pointer to the inserted node
  void delete_before(); // delete the node before this node
  void delete_after(); // delete the node after this node
};

// insert the int before this node
// return a pointer to the inserted node
Node* Node::insert_before(int d) {
  Node* new_node = new Node;
  new_node->data = d;
  new_node->next = this;
  new_node->previous = this->previous;
  this->previous->next = new_node;
  this->previous = new_node;
  return new_node;
  
}
// insert the int after this node
// return a pointer to the inserted node
Node* Node::insert_after(int d) {
  Node* new_node = new Node;
  new_node->data = d;
  new_node->previous = this;
  new_node->next = this->next;
  this->next->previous = new_node;
  this->next = new_node;
  return new_node;
  
}
// delete the node before this node
void Node::delete_before()
{
  Node* u = this->previous;
  u->next->previous = u->previous;
  u->previous->next = u->next;
  delete u;
  return;
  
}
// delete the node after this node
void Node::delete_after()
{
  Node* u = this->next;
  u->next->previous = u->previous;
  u->previous->next = u->next;
  delete u;
  return;
  
  
}

// Display the doubly linked list
void display_list(Node* header, Node* trailer) {
  Node* p=header->get_next();
  //Node* p=header; // uncomment this if want to display the header
  while (p!=trailer) {
    cout << p->data << ", ";
    p=p->get_next();
  }
  //cout << p->data << ", "; // uncomment this if want to display the trailer
  cout << endl;
}

// Test program
int main() {
  // Construct a linked list with header & trailer
  cout << "Create a new list" << endl;
  Node *header = new Node(-1);
  Node *trailer = new Node(-2);
  trailer->previous = header;
  header->next = trailer;
  cout << "list: ";
  display_list(header,trailer);
  cout << endl;
  
  // Insert 10 nodes at back with value 10,20,30,..,100
  cout << "Insert 10 nodes at back with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    trailer->insert_before(i);
  }
  cout << "list: ";
  display_list(header,trailer);
  cout << endl;

  // Insert 10 nodes at front with value 100,90,80,..,10
  cout << "Insert 10 nodes at front with value 100,90,80,..,10" << endl;
  for (int i=10;i<=100;i+=10) {
    header->insert_after(i);
  }
  cout << "list: ";
  display_list(header,trailer);
  cout << endl;
  
  // Delete the last 10 nodes
  cout << "Delete the last 10 nodes" << endl;
  for (int i=0;i<10;i++) {
    trailer->delete_before();  
  }
  cout << "list: ";
  display_list(header,trailer);
  cout << endl;
  
  // Delete the first 10 nodes
  cout << "Delete the first 10 nodes" << endl;
  for (int i=0;i<10;i++) {
    header->delete_after();
  }
  cout << "list: ";
  display_list(header,trailer);
  
  return 0;
  
}