//GraphTest.h
//Jaiden Gerig
#include <iostream>
#include <string>
#include "Graph.h"
using namespace std;

int main()
{       // you can use the following code to test your graph. 
        // you can also change your input file to do more testing
        // verify the results
		
		string str("mytest.txt");//source file for graph
		Graph graph(str);//create graph
		int start = 0;
		int end = 0;
		//get start and end vertices
		cout<<"Please enter the vertex you would like to start at\n";
		cin>>start;
		cout<<"Please enter the vertex you would like to end at\n";
		cin>>end;
		cout<<"Calculating path...\n";
		--start;
		--end;
		//print shortest path
		graph.printPath(graph.getVert(start), graph.getVert(end));
		
		return 0;
}