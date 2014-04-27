//Main.cpp
//Programming Assignment 1
//Jaiden Gerig
#include "std_lib_facilities_3.h"
#include "Question.h"
int StringToNumber ( const string &Text )//borrowed from cplusplus.com user Bazzy
{                               
	stringstream ss(Text);
	int result = 0;;
	return ss >> result ? result : 0;
}

bool is_number(const string &s)//borrowed from user Charles Salvia on stack overflow
{
    return !s.empty() && find_if(s.begin(), 
        s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

void vector_implementation()//Vector implementation
{
	vector<Question> vec_problems;
	int correct_count = 0;
	ifstream myfile_vec;
	myfile_vec.open ("Testfile.txt");
	Question read_in("Temp", 1, "answ1", "answ2","answ3");
	for(int i=0;i<15;++i)//reads in to vector
	{
		myfile_vec>>read_in;
		vec_problems.push_back(read_in);
	}
	srand(time(0));//ensures truly random shuffle by seeding system time
	random_shuffle(vec_problems.begin(),vec_problems.end());//shuffles vector
	for(int i=0;i<10;++i)//asks question + gets answer
	{
		bool correct = false;
		int answer = 0;
		string input;
		cout<<vec_problems[i];
		cin>>input;
		if(!is_number(input) || StringToNumber(input)<0 || StringToNumber(input)>5)
			throw runtime_error("Bad answer input");
		else
			answer = StringToNumber(input);
		if(answer == vec_problems[i].correct_answer_num())
		{
			++correct_count;
			cout<<"Awesome work! onto the next question\n";
		}
		else
			cout<<"Aw too bad you missed that one, try another!\n";
	}
	if(correct_count>6)
		cout<<"You got "<<correct_count<<" Right, and passed Nice job!\n";
	else
		cout<<"You got "<<correct_count<<" Right, and failed, better luck next time\n";
	return;
}

void list_implementation()//list implementation
{
	list<Question> all_problems;
	list<Question> problems;
	list<Question>::iterator l_itr;
	vector<Question> temp;
	int correct_count = 0;
	ifstream myfile;
	myfile.open ("Testfile.txt");
	Question read_in("Temp", 1, "answ1", "answ2","answ3");
	for(int i=0;i<15;++i)//reads in to list
	{
		myfile>>read_in;
		all_problems.push_back(read_in);
	}
	for(l_itr=all_problems.begin(); l_itr != all_problems.end();++l_itr)//converts to vector to shuffle
	{
		temp.push_back(*l_itr);
	}
	srand(time(0));//ensures truly random shuffle by seeding system time 
	random_shuffle(temp.begin(),temp.end());//shuffles temp vector
	for(int i=0;i<10;++i)//reads into new list
	{
		problems.push_back(temp[i]);
	}
	cout<<"Loop here\n";
	for(l_itr=problems.begin(); l_itr != problems.end() ;++l_itr)//asks question + gets answers
	{
		bool correct = false;
		int answer = 0;
		string input;
		cout<<*l_itr;
		cin>>input;
		if(!is_number(input) || StringToNumber(input)<0 || StringToNumber(input)>5)
			throw runtime_error("Bad answer input");
		else
			answer = StringToNumber(input);
		if(answer == l_itr->correct_answer_num())
		{
			++correct_count;
			cout<<"Awesome work! onto the next question\n";
		}
		else
			cout<<"Aw too bad you missed that one, try another!\n";
	}
	if(correct_count>6)
		cout<<"You got "<<correct_count<<" Right, and passed Nice job!\n";
	else
		cout<<"You got "<<correct_count<<" Right, and failed, better luck next time\n";
	return;
}
int main ()//asks user which implementation they'd like to use
{
	cout<<"Please pick which implementation you would like to use for this game\n";
	cout<<"1.)Vector\n";
	cout<<"2.)List\n";
	int choice = 0;
	cin>>choice;
	if(choice==1)
		vector_implementation();
	else if(choice==2)
		list_implementation();
	else
		throw runtime_error("Invalid Choice");
	return 0;
}