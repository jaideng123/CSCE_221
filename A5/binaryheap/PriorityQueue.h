//PrioirtyQueue.h
//Jaiden Gerig
#ifndef PRIORITY_H_
#define PRIORITY_H_

#include <cstdlib>
#include <iostream>
using namespace std;
template<typename ElemType> class Item;

class Locator {
private:
  int pqIndex;
public:
  Locator( int i = -1 ): pqIndex(i) { }
  const int getIndex() {return pqIndex;}
  void makeNull(){pqIndex = -1;}
  void setIndex(int index) { pqIndex = index;}
};
// output the item
template<typename ElemType>
ostream& operator<<(ostream& out, Locator& loc) {
	out<<"Position: "<<loc.getIndex()<<endl;
	return out;
}

// Assume key is integer
template<typename ElemType>
class Item {
private:
  int key;
  ElemType elem;
  int locIndex;
public:
  Item(const int k=0, const ElemType& e=ElemType(), int l=0): 
    key(k), elem(e), locIndex(l) { } //constructor
  const int getKey() const { return key; }
  const ElemType& getElem() const { return elem; }
  void setKey(const int k) { key = k; }
  void setElem(const ElemType& e) { elem = e; }
  int getLoc() {return locIndex;}
  void setLoc(int index){locIndex = index;}
  
};
// output the item
//This doesn't work, I don't know why, don't ask
/*
template<typename ElemType>
ostream& operator<<(ostream& out,Item<ElemType>& item) {
	out<<"Key: "<<item.getKey()<<endl;
	out<<"Element: "<<item.getElem()<<endl;
	out<<"Locator index: "<<item.getLoc()<<endl;
	return out;
}*/

template<typename ElemType>
class PQComp {
public:
  int operator()(const Item<ElemType>& e1, const Item<ElemType>& e2) const {
    return e1.getKey() - e2.getKey();
  }
};

#include <stdexcept>
struct EmptyPriorityQueue : std::range_error {
  explicit EmptyPriorityQueue(char const* msg=NULL): range_error(msg) {}
};

#include "BinaryHeap.h"
template<typename ElemType>
class PriorityQueue {
protected: 
  typedef Item<ElemType> _Item;
  typedef PQComp<ElemType> _PQComp;
private: 
  BinaryHeap<_Item, _PQComp> T;  
  static const int DEF_SIZE = 10;
public: // class PriorityQueue cont.
	void printLocStructure(){T.printLocvec();}//output locator
	int getSize(){return T.getSize();}
	Locator getLoc(int index){return T.getLoc(index);}
  PriorityQueue(int size = DEF_SIZE) : T(size) { }
  void printAll(){ // output the priority queue + loc structure
		cout<<"Priority Queue"<<endl;
		cout<<T<<endl;
		printLocStructure();
	}
	
  bool isEmpty() const { return T.isEmpty(); }
  
  //inserts item into heap
  void insertItem(const int k, const ElemType& e) { 
	Locator temp;
	T.addLoc(temp,e);
	Item<ElemType> temp2(k,e,e);
	T.insert(temp2);
  }
  
  //return min locator
  Locator min() throw (EmptyPriorityQueue) {
	return T.getLoc(T.findMin().getLoc());
  }
  
  //Remove corresponding item of locator
  void remove(Locator loc) throw (EmptyPriorityQueue) {
	int index = loc.getIndex();
	T.remove(index);
  }
  
  //replace key of corresponding locator
  void replaceKey(Locator loc, int k) {
	T.setElemKey(loc.getIndex(),k);
  }
  
  //build priority queue from arrays, note: n = size
  void createPriorityQueue(int kArray[], ElemType xArray[], int locIndexArray[], int n) {
	for(int i=0;i<n;++i)
		insertItem(kArray[i],xArray[i]);
  }
  int getKey(Locator loc) {
	return T.getElem(loc).getKey();
  }
  ElemType getElem(Locator loc) {
	return T.getElem(loc).getElem();
  }
  //return min item
  const ElemType& minElement() throw (EmptyPriorityQueue) {
    if (T.isEmpty())
    throw EmptyPriorityQueue();
    return T.findMin().getElem();
  }
  //return min key
  const int minKey() throw (EmptyPriorityQueue) {
    if (T.isEmpty()) throw EmptyPriorityQueue();
    return T.findMin().getKey();
  }
  //remove min item
  void removeMin() throw (EmptyPriorityQueue) {
    if (T.isEmpty())
    throw EmptyPriorityQueue();
    T.deleteMin();
  }  
};
#endif /*PRIORITY_H_*/