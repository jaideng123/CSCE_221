//BinarySearchTree.cpp
//Jaiden Gerig
#include "BinarySearchTree.h"
#include <stdexcept>

double BinaryNode::size(BinaryNode *t) { //recursive
	if(t == NULL)
		return 0;
	else
		return 1 + size(t->left) + size(t->right);
}

int BinaryNode::height(BinaryNode *t) { //recursive
	if(t == NULL)
		return -1;
	else {
		int hlf = height(t->left), hrt = height(t->right);
		return 1 + max(hlf,hrt);
	}
}
BinaryNode *BinaryNode::copy( ) { // recursive
	BinaryNode *root = new BinaryNode(key);
	if(left != NULL)
		root->left = left->copy();
	if(right != NULL)
		root->right = right->copy();
	return root;
}

// it finds a node containing element x
BinaryNode *BinarySearchTree::rFind(int x, BinaryNode *t){	
	while(t != NULL){
		if(x < t->key) 
			t = t->left;
		else if(x > t->key) 
			t = t->right;
		else 
			return t; // found
	}
	throw runtime_error("Item not found!");
}
// it inserts a new node containing the element x
BinaryNode *BinarySearchTree::rInsert(int x, BinaryNode *t) 
{
	if(t == NULL) 
		t = new BinaryNode(x);
	else if(x < t->key)
		t->left = rInsert(x, t->left);
	else if(x > t->key)
		t->right = rInsert(x, t->right);
	else
		throw runtime_error("DUPLICATE ADDED");
	return t;
}
BinaryNode *BinarySearchTree::rRemove(int x, BinaryNode *t) //throw (ItemNotFound)
{ 
	if(t == NULL)
		throw runtime_error("ITEM NOT FOUND");
	if(x < t->key)
		t->left = rRemove(x, t->left);
	else if(x > t->key)
		t->right = rRemove(x, t->right);
	else if(t->left != NULL && t->right != NULL)// item x is found; t has two children
	{
		t->key = findMin(t->right)->key;
		t->right = removeMin(t->right);
	} 
	else { //t has only one child
		BinaryNode *node = t;
		t = (t->left != NULL) ? t->left : t->right;
		delete node;
	}
	return t;
}
// delete a tree rooted at "root"
void BinarySearchTree::deleteTree(BinaryNode *root)
{
	if (root == NULL) return;
	if (root->left != NULL)
		deleteTree(root->left);
	if (root->right != NULL)
		deleteTree(root->right);
	delete root;
}
BinaryNode *BinarySearchTree::findMin(BinaryNode *t)
{
	if(t == NULL)
		throw 2;
	while(t->left != NULL)
		t = t->left;
	return t;
}
BinaryNode *BinarySearchTree::removeMin(BinaryNode *t)
{
	if(t == NULL)
		throw 2;
	if(t->left != NULL)
		t->left = removeMin(t->left);
	else
	{
		BinaryNode *node = t;
		t = t->right;
		delete node;
	}
	return t;
}
void BinarySearchTree::calcDepth(BinaryNode* t, int depth)
{
	if (t != NULL)
	{
		calcDepth(t->left, depth + 1);
		t->searchCost = depth;
		calcDepth(t->right, depth + 1);
	}
}
void BinarySearchTree::rPrint(BinaryNode *root)
{
	if(size() > 16)
	{
		ofstream ofs(ofile.c_str(), ios::app);
		if (root != NULL)
		{
			rPrint(root->left);
			ofs << root->key << "[" << root->searchCost << "] ";
			totalCost += root->searchCost;
			rPrint(root->right);
		}
	}
	else
	{
		if (root != NULL)
		{
			rPrint(root->left);
			cout << root->key << "[" << root->searchCost << "] ";
			totalCost += root->searchCost;
			rPrint(root->right);
		}
	}
}
void BinarySearchTree::printLevelByLevel()
{
	ofstream ofs(ofile.c_str());
	queue<BinaryNode*> currentlevel, nextlevel;
	currentlevel.push(root);
	bool allChildNull = false;
	
	while(!currentlevel.empty() && !allChildNull)
	{
		allChildNull = true;
		while (!currentlevel.empty())
		{
			BinaryNode* node = currentlevel.front();
			currentlevel.pop();

			if (node == NULL)
			{
				if(size() > 16)
					ofs << "X" << " ";
				else
					cout << "X" << " ";
			}
			else
			{
				if(size() > 16)
					ofs << node->key << " ";
				else
					cout << node->key << " ";
			}
			if(node == NULL)
			{
				nextlevel.push(NULL);
				nextlevel.push(NULL);
			}
			else
			{
				nextlevel.push(node->left);
				nextlevel.push(node->right);
				if(node->left != NULL || node->right != NULL)
					allChildNull = false;
			}
		}
		if (currentlevel.empty())
		{
			if(size() > 16)
				ofs << endl;
			else
				cout << endl;
			swap(currentlevel, nextlevel);
		}
	}	
}