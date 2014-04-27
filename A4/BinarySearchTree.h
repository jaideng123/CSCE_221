//BinarySearchTree.h
//Jaiden Gerig
#include <iostream>
#include <cstddef>
#include <queue>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
class BinaryNode {
private:
	friend class BinarySearchTree;
	int key = 0;
	int searchCost = 0;
	BinaryNode *left, *right;
public:
	BinaryNode(int el = 0,int sc = 1, BinaryNode *lt = NULL, BinaryNode *rt = NULL) : //constructor
	key(el), searchCost(sc), left(lt), right(rt) { } 
	// functions
	BinaryNode *getLeft() { return left; }
	BinaryNode *getRight() { return right; }
	int getElem() { return key; }
	int getCost(){ return searchCost; }
	double size(BinaryNode *t);
	int height(BinaryNode *t);
	void set_searchCost(int cost){searchCost = cost;}
	int get_searchCost(){return searchCost;}
	BinaryNode *copy();
};

class BinarySearchTree {// uses the class BinaryNode
private: 
	BinaryNode *root; 
	BinaryNode* rRemove(int x, BinaryNode *t);
	BinaryNode* rInsert(int x, BinaryNode *t);
	BinaryNode* rFind(int x, BinaryNode *t);
	void rPrint(BinaryNode *root);
	void deleteTree(BinaryNode *root);
	double totalCost = 0;
	string ofile = "Output.txt";
public: // constructor
	BinarySearchTree() { root = NULL; }
	~BinarySearchTree() { deleteTree(root); root = NULL; }
	int size() {return(root==NULL) ? 0 : root->size(root);}
	int height() {return(root==NULL) ? 0 : root->height(root);}
	void insert(int x){ 
		root = rInsert(x, root);
		calcDepth(root, 1);
	}
	void remove(int x){ 
	root = rRemove(x, root); 
	calcDepth(root, 1);
	}
	BinaryNode *find(int x) { return rFind(x, root); }
	bool isEmpty(){return root == NULL; }
	BinaryNode* findMin(BinaryNode *t);
	BinaryNode* removeMin(BinaryNode *t);
	BinaryNode* getRoot(){ return root; }
	void printAll(){ 
		totalCost = 0;
		ofstream ofs(ofile.c_str(), ios::trunc);
		rPrint(root);
		double avg = totalCost/size();
		cout<<endl<<"AVG Search Cost: "<<avg;
		cout<<endl;
	}
	void printLevelByLevel();
	void calcDepth(BinaryNode* t, int depth);
	void set_ofile(string of){ofile = of;}
};