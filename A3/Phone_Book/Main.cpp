//Phone book main
//Jaiden Gerig
#include <iostream>
#include <string>
#include <cstdio>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <stdexcept>
#include "Record.h"
#include "TemplateDoublyLinkedList.h"
using namespace std;

void getData(string infile,vector<DoublyLinkedList<Record> >& vdll ){
	ifstream myfile(infile);
	if(myfile.is_open())
	{
		string tempLine;
		while(!myfile.eof()){
			getline (myfile,tempLine);
			string lName = tempLine;
			getline (myfile,tempLine);
			string fName = tempLine;
			getline (myfile,tempLine);
			string UIN = tempLine;
			getline (myfile,tempLine);
			string pNumber = tempLine;
			getline (myfile,tempLine);
			Record rtemp(lName,fName,UIN,pNumber);
			vdll[rtemp.get_lName()[0] - 65].insert(rtemp);
		}
		return;
	}
	else
		throw runtime_error("file is not open");
}

void display(vector< DoublyLinkedList<Record> >& v){
	for(int i=0; i<v.size(); ++i)
		cout<<v[i];
}
void search(vector< DoublyLinkedList<Record> >& v){
	string searchTerm;
	vector<Record> matches1;//first set of matches
	vector<Record> matches2;//second set
	cout<<"Please enter the last name of the person you are searching for \n";
	cin>>searchTerm;
	int index = searchTerm[0] - 65;
	DListNode<Record>* tempPtr = v[index].getFirst();
	while(tempPtr->getNext() != NULL)//looks for lname
	{
		if(tempPtr->getElem().get_lName() == searchTerm)
			matches1.push_back(tempPtr->getElem());
		tempPtr = tempPtr->getNext();
	}	
	if (matches1.size() == 0)
	{
		cout<<"No matches found! Please try again\n";
		return;
	}
	else if (matches1.size() == 1)
	{
		cout<<"Match found!\n\n";
		cout<<matches1[0];
		return;
	}
	else//look for first name
	{
		cout<<"Multiple matches found! \n";
		cout<<"Please enter the first name of the person you are searching for\n";
		cin>>searchTerm;
		for(int i = 0; i<matches1.size();++i)//looks for fname
		{
			if(matches1[i].get_fName() == searchTerm)
				matches2.push_back(matches1[i]);
		}
		if(matches2.size() == 0)
		{
		cout<<"No matches found! Please try again\n";
		return;
		}
		else if (matches2.size() == 1)
		{
		cout<<"Match found!\n\n";
		cout<<matches2[0];
		}
		else//look for UIN
		{
			cout<<"Multiple matches found! \n";
			cout<<"Please enter the UIN of the person you are searching for\n";
			cin>>searchTerm;
			for(int i = 0; i<matches2.size();++i)
			{
				if(matches2[i].get_UIN() == searchTerm)
				{
				cout<<"Match found!\n\n";
				cout<<matches2[i];
				return;
				}	
			}
			cout<<"No matches found! Please try again\n";
			return;
		}
	}
}
int main(){
	cout << "Fetching List..." << endl<<endl;
	vector< DoublyLinkedList<Record> > phoneBook(26);
	getData("PhoneBook.txt", phoneBook);
	cout<<"Done!\n\n\n";
	int choice = 0;
	cout<<"Please enter the number corresponding with what you'd like to dp\n";
	cout<<"1) Display Phone Book \n";
	cout<<"2) Search Phone Book \n";
	cout<<"3) Exit program \n";
	cin>>choice;
	switch (choice) {
		case 1:
		display(phoneBook);
		break;
		case 2:
		search(phoneBook);
		break;
		case 3:
		return 0;
		break;
		default:
		throw runtime_error("Bad Input");
	}
	return 0;
}