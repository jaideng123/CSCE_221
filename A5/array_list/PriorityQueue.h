//PrioirtyQueue.h
//Jaiden Gerig
#include <cstdlib>
#include <iostream>
using namespace std;
template<typename ElemType> class Item;
class Locator {
private:
  int pqIndex; //an array index of the pointed item
public:
  Locator( int i = -1 ): pqIndex(i) { }
  const int getIndex() {return pqIndex;}
  void makeNull(){pqIndex = -1;}
  void setIndex(int index) { pqIndex = index;}
};
// output the item index
ostream& operator<<(ostream& out,Locator& loc) {
	out<<"Position: "<<loc.getIndex()<<endl;
	return out;
}

// Assume key is integer
template<typename ElemType>
class Item {
private:
  int key;
  ElemType elem;
  int locIndex; // a vector index of the corresonding locator 
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

#include <climits>
#include <vector>
template<typename ElemType>
class PriorityQueue {

protected: 
  typedef Item<ElemType> _Item;
  typedef PQComp<ElemType> _PQComp;
private: 
  vector<_Item> T;
  
  _PQComp comp;
  Locator null;
  vector<Locator> locVec = vector<Locator>(10,null); // locator vector
  
public: // class PriorityQueue cont.
  PriorityQueue() { }
  bool isEmpty() const { return T.empty(); }
  int getSize() {return T.size();}
  Item<ElemType> getItem(int index){return T[index];}
  Locator getLoc(int index){return locVec[index];}
  void printLocVec(){//prints out locator structure
	cout<<"Locator structure:"<<endl;
	for(int i=0;i<locVec.size();++i){
		cout<<"Locator: "<<i<<" = "<<locVec[i].getIndex()<<endl;
	}
  }
  //inserts item at end of vector
  void insertItem(const int k, const ElemType& e, int locIndex) {
	Locator temp(T.size());
	locVec[locIndex] = temp;
	T.push_back(Item<ElemType>(k,e,locIndex));
  }
  
  //return min locator
  Locator min() throw (EmptyPriorityQueue) {
	if(isEmpty()) 
		throw EmptyPriorityQueue();
	Item<ElemType>* temp = &T[0];
	//traverse vector
	for(int i=1; i<T.size();++i){
		if(comp(*temp,T[i]) > 1)
			temp = &T[i];
	}
	return locVec[temp->getLoc()];
  }
  //Remove corresponding item of locator
  void remove(Locator loc) throw (EmptyPriorityQueue) {
	if(isEmpty()) 
		throw EmptyPriorityQueue();
	int counter = 0;
	//shift array over
	for(int i=loc.getIndex(); i < (T.size() - 1); ++i){
		T[i].setKey(T[i+1].getKey());
		T[i].setElem(T[i+1].getElem());
		locVec[T[i+1].getLoc()].setIndex(i);
		T[i].setLoc(T[i+1].getLoc());
		++counter;
		}
	//uncomment to measure complexity
	//cout<<"# of comparisons: "<<counter<<endl;
	T.erase(T.begin()+(T.size()-1));
	loc.makeNull();
	}
	//replace key of corresponding locator
  void replaceKey(Locator loc, int k) {
	T[loc.getIndex()].setKey(k);
  }
  //build priority queue from arrays, note: n = size
  void createPriorityQueue(int kArray[], ElemType xArray[], int locIndexArray[], int n) {
	for(int i=0;i<n;++i)
		insertItem(kArray[i],xArray[i],locIndexArray[i]);
  }
  //return key
  int getKey(Locator loc) {
	return T[loc.getIndex()].getKey();
  }
  //return element
  ElemType getElem(Locator loc) {
	return T[loc.getIndex()].getElem();
  }
  //return whole item
  Item<ElemType> getItem(Locator loc){
  return T[loc.getIndex()];
  }
};
// output the priority queue
template<typename ElemType>
ostream& operator<<(ostream& out, PriorityQueue<ElemType>& pq) {
	for(int i=0;i< pq.getSize();++i){
		Item<ElemType> temp = pq.getItem(i);
		out<<"List Index: "<<i<<endl;
		out<<"Key: "<<temp.getKey()<<endl;
		out<<"Element: "<<temp.getElem()<<endl;
		out<<"Locator index: "<<temp.getLoc()<<endl;
		out<<endl;
	}
	return out;
}