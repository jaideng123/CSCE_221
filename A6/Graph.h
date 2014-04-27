#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
//Graph.h
//Jaiden Gerig
#include <string>
#include <vector>
#include <climits>
#include <stdexcept>
#include "Vertex.h"
#include "Edge.h"
#include "PriorityQueue.h"

using namespace std;

class Edge;
class Vertex;

class Graph{

private:
	vector<Vertex*> vertList;
	vector<Edge*> edgeList;
	int comparisons = 0;
public:
	Graph(string filename);
	~Graph();
	vector<Vertex*> getVertices() const {return vertList;}
	int getNumVertices() const { return vertList.size();}
	void PrintGraph();
	void dijkstra(Vertex *src);//sets up graph from source node
	Vertex* getVert(int i){
	if (i > vertList.size())
		throw runtime_error("Vertex does not exist in this graph");
	return vertList[i];}
	void printPath(Vertex *src, Vertex *end);
};
#endif