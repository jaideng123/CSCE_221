//Question.h
//Programming Assignment 1
//Jaiden Gerig
#ifndef QUESTION_H
#define QUESTION_H

#include "std_lib_facilities_3.h"

class Question
{
	private:
	string quest = "NULL";
	vector<string> answers;
	int correct_answer = 0;
	bool solved = false;
	
	public:
	Question(string inquest,int correct,string A1,string A2, //must be initialized with a question correct answer
	string A3="NULVAL", string A4="NULVAL",string A5="NULVAL");//and at least 2 answer choices
	bool is_correct(int ans);
	bool is_solved(){ return solved;}
	string get_question() const {return quest;}
	string get_answer_choice(int i) const {if(i<answers.size()+1) return answers[i-1];//returns string of answer choice
											else throw bad_function_call();}
	string get_correct_answer() const {return get_answer_choice(correct_answer);}
	int correct_answer_num() const {return correct_answer;}
	int number_of_answers() const {return answers.size();}
	void change_question(string newquest);
	void remove_answer(int ans);
	void add_answer(string newans);
	void empty_answers(){answers.clear();}	
	void change_correct(int new_cor){if(new_cor>0 && new_cor<6) correct_answer=new_cor;
									else throw bad_function_call();}
};
int StringToNum( const string &Text );
bool is_num(const string &s);
inline ostream& operator<<(ostream& os, const Question& q)//inlined due to compiler restrictions
{
	os << "Question: "<<q.get_question()<<"\n";
	for(int i=0;i<q.number_of_answers();++i)
		os << "\n\t"<<(i+1)<<".) "<<q.get_answer_choice(i+1);
	os << "\n";
	return os;
}
inline istream& operator>>(istream& is, Question& qq)//inlined due to compiler restrictions
{
	qq.empty_answers();//clear question to be read into
    string inq, A1, A2, A3, A4, A5;
	string test;
	int correct_ans= 0;
	getline(is,inq);
	while(inq=="")//eats up empty lines
		getline(is,inq);
	qq.change_question(inq);
	getline(is, A1);
	qq.add_answer(A1);
	getline(is, A2);
	qq.add_answer(A2);
	getline(is, test);
	while(!is_num(test))//keeps grabbing answers till it finds a number
	{
		qq.add_answer(test);
		getline(is, test);
	}
	correct_ans = StringToNum(test);
	qq.change_correct(correct_ans);
    return is;
}

#endif