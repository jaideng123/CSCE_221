//Number Set Generator
//Jaiden Gerig
#include "std_lib_facilities_3.h"
void inc_set(string name,int limit)
{
	string fname = name + "_inc.txt";
	ofstream ofile1(fname);
	if(ofile1.is_open())
	{
		ofile1<<limit<<endl;
		for(int i=1;i<=limit;++i)
			ofile1 << i << endl;
	}
	else
		throw runtime_error("BAD FILE");
	return;
}

void dec_set(string name,int limit)
{
	string fname = name + "_dec.txt";
	ofstream ofile2(fname);
	if(ofile2.is_open())
	{
		ofile2<<limit<<endl;
		for(int i=limit;i>0;--i)
			ofile2 << i << endl;
	}
	else
		throw runtime_error("BAD FILE");
	return;
}

void rand_set(string name,int limit)
{
	string fname = name + "_rand.txt";
	ofstream ofile3(fname);
	if(ofile3.is_open())
	{
		ofile3<<limit<<endl;
		for(int i=0;i<limit;++i){
			srand(time(0)+i);
			int temp = rand();
			ofile3 << temp % 100000<< endl;
		}
	}
	else
		throw runtime_error("BAD FILE");
	return;
}
int main(){
	string setname;
	int intnum = 0;
	cout<<"Please enter the name you would like to have\n";
	cout<<"for your 3 sets\n";
	cin>>setname;
	cout<<"Please Enter the amount of integers you would like your sets to contain\n";
	cin>>intnum;
	cout<<"Thank you, i will now generate your sets for you\n\n";
	
	cout<<"Building increasing set...\n";
	inc_set(setname, intnum);
	cout<<"Set complete!\n\n";
	
	cout<<"Building decreasing set...\n";
	dec_set(setname, intnum);
	cout<<"Set complete!\n\n";
	
	cout<<"Building random set...\n";
	rand_set(setname, intnum);
	cout<<"Set complete!\n\n";
	
	
	return 0;
}