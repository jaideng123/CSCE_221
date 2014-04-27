//BinaryHeap.h
//Jaiden Gerig
#ifndef HEAP_H_
#define HEAP_H_

#include "PriorityQueue.h"
#include <stdexcept>
#include <iostream>
#include <vector>
using namespace std;
struct EmptyHeap : std::range_error {
  explicit EmptyHeap(char const* msg=NULL): range_error(msg) {}
};

template<typename ElemType, typename Comp>
class BinaryHeap {
private:
  Comp comp; //comparator class
  
  int curSize; //number of elements in heap
  
  ElemType *array; //(dynamic) heap array
  
  int length;//the length of the array
  
  Locator null;//
  vector<Locator> locVec = vector<Locator>(500,null); // locator vector
  
  int comparisons = 0;
  
  static const int DEF_SIZE = 500;
  
  void getNewArray(int newSize) {
    array = new ElemType[newSize];
    length = newSize;
  }
  
  // double the heap array if it is full
  void checkSize() {
    if (curSize == length) {
      ElemType *oldArray = array;
      getNewArray(2*curSize);
      for (int i = 0; i < curSize; i++)
        array[i] = oldArray[i];
      delete [] oldArray;
    }
  }
  
  void walkUp(int hole);
  void walkDown(int hole);
  
public: // templated class BinaryHeap (cont)
  BinaryHeap(int size = DEF_SIZE) {
    //constructor
    curSize = 0;
    getNewArray(size);
  }
  
  ElemType& findMin() throw (EmptyHeap) {
    if ( isEmpty() ) throw EmptyHeap();
    return array[0];
  }  
  
  bool isEmpty( ) const { return curSize == 0; }
  void insert(const ElemType& x);
  void deleteMin() throw (EmptyHeap);
  void toss(ElemType x); // (from Heap slides)
  void buildHeap(); // (from Heap slides)
  void remove(int index);
  void addLoc(Locator loc, int index){locVec[index] = loc;}
  int getcomparisons(){return comparisons;}
  Locator getLoc(int index){return locVec[index];}
  int getSize(){return curSize;}
  ElemType getElem(Locator loc){return array[loc.getIndex()];}
  ElemType getElem(int index){return array[index];}
  
  void setElemKey(int index, int newKey){
	array[index].setKey(newKey);
	//reshuffle pq to make sure key is still correctly aligned
	walkUp(index);
	walkDown(index);
  }
  
  void printLocvec(){
	cout<<"Locator structure:"<<endl;
	for(int i=0;i<locVec.size();++i){
		cout<<"Locator: "<<i<<" = "<<locVec[i].getIndex()<<endl;
	}
  }
  
};

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::remove(int index){
	checkSize();
	locVec[array[index].getLoc()].makeNull();
	array[index] = array[ --curSize ];
	walkDown(index);
}
 

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::insert(const ElemType& x) {
  checkSize();
  int hole = curSize++;
  array[hole] = x;
  walkUp(hole);
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::deleteMin() throw (EmptyHeap) {
  locVec[array[0].getLoc()].makeNull();
  array[0] = array[ --curSize ];
  //decrease size
  walkDown(0);
}

// (extracted from the original insert function)
template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::walkUp(int hole) {
  ElemType key=array[hole];
  for ( ; hole > 0 && comp(array[(hole-1)/2], key) > 0; hole = (hole-1)/2) {
	//locVec[array[hole].getLoc()].setIndex((hole-1)/2);
    array[hole] = array[(hole-1)/2];
	locVec[array[(hole-1)/2].getLoc()].setIndex(hole);
  }
  array[hole] = key;
  locVec[array[hole].getLoc()].setIndex(hole);
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::walkDown(int hole) {
  int child; 
  int counter= 0;
  ElemType key = array[hole];
  for ( ; 2*hole+1 < curSize; hole = child) {
    child = 2*hole+1;
	comparisons++;
    if (child != curSize-1 && comp(array[child], array[child+1]) > 0){
      child++;
	 }
    // right child = 2*hole+2
	counter++;
    if (comp(key, array[child]) > 0) {
      array[hole]=array[child];
	  locVec[array[hole].getLoc()].setIndex(child);
    }
    else break;
  }
  array[hole] = key;
  locVec[array[hole].getLoc()].setIndex(hole);
  for(int i = 0;i<curSize;++i)//double check all locators
	if(locVec[array[i].getLoc()].getIndex() != -1)
		locVec[array[i].getLoc()].setIndex(i);
}

// insert into array without maintaining heap order
template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::toss(ElemType x) {
  checkSize();
  array[ curSize++ ] = x;
  locVec[x.getLoc()].setIndex(curSize);
}

// bottom-up heap construction
template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::buildHeap() {
  for (int i = (curSize-2)/2; i >= 0; i--) walkDown(i);
}


template<typename ElemType, typename Comp>
ostream& operator<<(ostream& out, BinaryHeap<ElemType, Comp>& bh) {
	for(int i=0;i< bh.getSize();++i){
		out<<"List Index: "<<i<<endl;
		out<<"Key: "<<bh.getElem(i).getKey()<<endl;
		out<<"Element: "<<bh.getElem(i).getElem()<<endl;
		out<<"Locator index: "<<bh.getElem(i).getLoc()<<endl;
		out<<endl;
	}
	return out;
}
#endif /* HEAP_H_ */