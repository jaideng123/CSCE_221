//Vertex.h
//Jaiden Gerig
#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Edge.h"

using namespace std;

class Graph;
class Edge;

class Vertex {

private:
	vector<Edge*> inList; // source vertex
    vector<Edge*> outList; // end vertex 
	int id;
	friend class Graph;
	int d = 0;//Distance to source node
	Vertex* p;//Parent from source node
public:
	Vertex(){
		id = -1;
		p = NULL;
	}
	Vertex(int sid){id = sid;}
	int getID() const{return id;}
	vector<Edge*> getOutEdges() const{return outList;}
	vector<Edge*> getInEdges() const{return inList;}
	int getD(){return d;}
	void setD(int nd){d = nd;}
	void setP(Vertex* np){p = np;}
	Vertex& operator=(Vertex rhs){
		id = rhs.id;
		d = rhs.d;
		p = rhs.p;
		for(int i = 0;i< rhs.inList.size();++i)
			inList.push_back(rhs.inList[i]);
		for(int i = 0;i< rhs.outList.size();++i)
			outList.push_back(rhs.outList[i]);
		return *this;
	}
};

#endif