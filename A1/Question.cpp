//Question.cpp
//Programming Assignment 1
//Jaiden Gerig
#include "std_lib_facilities_3.h"
#include "Question.h"

Question::Question(string inquest,int correct,string A1,string A2, string A3, string A4,string A5):
	quest(inquest), correct_answer(correct)
{
	answers.push_back(A1);
	answers.push_back(A2);
	if(A3 != "NULVAL")
		answers.push_back(A3);
	else if(A4 != "NULVAL")
		answers.push_back(A4);
	else if(A5 != "NULVAL")
		answers.push_back(A5);
}

bool Question::is_correct(int ans)
{
	if(ans == correct_answer)
	{
		solved = true;
		return true;
	}
	else
		return false;
}

inline bool operator==(const Question& q1, const Question& q2)
{
	if(q1.get_question() == q2.get_question())
	{
		if(q1.number_of_answers() == q2.number_of_answers())
		{
			for(int i=0;i<q1.number_of_answers();++i)
			{
				if(q1.get_answer_choice(i+1)!= q2.get_answer_choice(i+1))
					return false;
			}
			return true;
		}
		else
			return false;
	}
	else
		return false;
}
void Question::change_question(string newquest)
{
	quest = newquest;
	return;
}
void Question::remove_answer(int ans)
{
	answers.erase(answers.begin() + (ans-1));
	return;
}
void Question::add_answer(string newans)
{
	answers.push_back(newans);
	return;
}
bool is_num(const string &s)//borrowed from user Charles Salvia on stack overflow
{
    return !s.empty() && find_if(s.begin(), 
        s.end(), [](char c) { return !isdigit(c); }) == s.end();
}
int StringToNum( const string &Text )//borrowed from cplusplus.com user Bazzy
{                               
	stringstream ss(Text);
	int result = 0;;
	return ss >> result ? result : 0;
}