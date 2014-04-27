//Record Class
//Jaiden Gerig
#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <stdexcept>
using namespace std;
class Record{
private:
	string lName, fName, UIN, pNumber;
	
public:
	Record(string in_lName="", string in_fName="", string in_UIN="000000000", 
	string in_pNumber=""): lName(in_lName), fName(in_fName), pNumber(in_pNumber) 
	{
	if(in_UIN.length() != 9)
		throw invalid_argument("UIN MUST BE 9 DIGITS LONG!");
	else	
		UIN = in_UIN;
	}
	const string get_lName(){return lName;}
	const string get_fName(){return fName;}
	const string get_UIN(){return UIN;}
	const string get_pNumber(){return pNumber;}
	void set_lName(string in_lName){ lName = in_lName;}
	void set_fName(string in_fName){ fName = in_fName;}
	void set_pNumber(string in_pNumber){pNumber = in_pNumber;}
	void set_UIN(string in_UIN){
	if(in_UIN.length() != 9)
		throw invalid_argument("UIN MUST BE 9 DIGITS LONG!");
	else	
		UIN = in_UIN;}
};
ostream& operator<<(ostream& out,  Record& rec) {
	if(rec.get_lName() == "")
		return out;
	else
	{
		out<<"NAME: "<<rec.get_lName()<<", "<<rec.get_fName()<<"\n";
		out<<"UIN: "<<rec.get_UIN()<<"\n";
		out<<"PHONE NUMBER: "<<rec.get_pNumber()<<"\n";
	}
	return out;
}
inline bool operator< ( Record& lhs, Record& rhs){ 
	if(lhs.get_lName() < rhs.get_lName())
		return true;
	else if(lhs.get_fName() < rhs.get_fName())
		return true;
	else if(lhs.get_UIN() < rhs.get_UIN())
		return true;
	else
		return false;
}
	
	
	