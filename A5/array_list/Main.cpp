//main.cpp
//Jaiden Gerig
#include "PriorityQueue.h"
#include <iostream>
#include <vector>
using namespace std;
/*
  Key-element integer pairs. The key represents the distance
  from the BWI airport to a city. The element is the city ID
  The example is extracted from the textbook figure 13.15(g) at p.642.

  //key (distance), element (city ID) 
  2467 0 // SFO 
  3288 1 // LAX 
  621 2 // ORD 
  1423 3 // DFW 
  84 4 // JFK 
  371 5 // BOS 
  328 6 // PVD 
  0 7 // BWI 
  946 8 // MIA 	
*/

int main() {
	PriorityQueue<int> mpq;
	cout<<"Building priority queue..."<<endl;
	int kArray[] = {2467, 3288, 621, 1423, 84, 371, 328, 0, 946};
	int xArray[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	mpq.createPriorityQueue(kArray,xArray,xArray,9);
	cout<<mpq;
	mpq.printLocVec();
	cout<<"Done!"<<endl;
	Locator m;
	cout<<"Removing Min:\n"<<endl;
	m = mpq.min();
	cout<<"Key: "<<mpq.getKey(m)<<endl;
	cout<<"Element: "<<mpq.getElem(m)<<endl;
	mpq.remove(m);
	cout<<mpq;
	mpq.printLocVec();
	
  // sort
	cout<<"Sorting queue..."<<endl;
	while(mpq.getSize() > 0){
		m = mpq.min();
		cout<<"Key: "<<mpq.getKey(m)<<endl;
		cout<<"Element: "<<mpq.getElem(m)<<endl;
		mpq.remove(m);
	}
	cout<<"Queue sorted!"<<endl;
  // create PQ again; and assign locSearchVec according to the city name
	cout<<"Rebuilding priority queue..."<<endl;
	for(int i=0; i<9;++i){
		mpq.insertItem(kArray[i],xArray[i],xArray[i]);
	}
	cout<<mpq<<endl;
	cout<<"Priority queue rebuilt!"<<endl;
	mpq.printLocVec();
  // replace the key of JFK to 2000
	cout<<"Would you like to replace a key?"<<endl;
  char choice;
  cin>>choice;
  if(choice == 'y' || choice == 'Y'){
	cout<<"Please enter the locator ID for the item you would like to change"<<endl;
	int lIndex = 0;
	cin>>lIndex;
	cout<<"Please enter the new key for the item you would like to change"<<endl;
	int nKey = 0;
	cin>>nKey;
	cout<<"Changing key..."<<endl;
	m = mpq.getLoc(lIndex);
	mpq.replaceKey(m,nKey);
	cout<<mpq;
	mpq.printLocVec();
	cout<<"Key changed!"<<endl;
	}
	
}
