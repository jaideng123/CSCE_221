//Main.cpp
//Jaiden Gerig
#include "BinarySearchTree.h"
#include <iostream>
#include <sstream>
#include <cstddef>
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

void runTest(string instring)
{
	BinarySearchTree* bst = new BinarySearchTree;
	bst->set_ofile(instring + "-output.txt");
	ifstream input(instring.c_str());
	if(input.is_open())
	{
		string line;
		while (getline(input, line))
		{
			istringstream iss(line);
			int n;
			while (iss >> n)
			{
				bst->insert(n);
			}
		}
	}
	else
		throw runtime_error("BAD FILENAME");
	bst->printAll();
	cout<<endl;
	bst->printLevelByLevel();
	cout<<"\n\nWould you like to remove a node?\n";
	string choice;
	cin>>choice;
	if(choice == "yes" ||choice == "y")
	{
		cout<<"Which node would you like to remove?\n";
		int remnode = 0;
		cin>>remnode;
		bst->remove(remnode);
		cout<<"Here is your new tree:\n";
		bst->printAll();
		cout<<endl;
		bst->printLevelByLevel();
	}
	else
		cout<<"Exiting...\n";
}
void allTests()
{
	for(int i = 1; i<5;++i)
	{
		ostringstream oss;
		oss << i;
		runTest("test-files/"+oss.str()+"p");
		cout<<endl;
	}
	cout<<endl;
	for(int i = 1; i<5;++i)
	{
		ostringstream oss;
		oss << i;
		runTest("test-files/"+oss.str()+"r");
		cout<<endl;
	}
	cout<<endl;
	for(int i = 1; i<5;++i)
	{
		ostringstream oss;
		oss << i;
		runTest("test-files/"+oss.str()+"l");
		cout<<endl;
	}
	cout<<endl;
}
int main(){
	string instring;
	cout<<"Please enter the filename to build a tree of it\n";
	cout<<"OR to run all tests at once type in AUTO\n";
	cin>>instring;
	if(instring == "AUTO")
		allTests();
	else
		runTest(instring);
	
	return 0;
}