//Graph.cpp
//Jaiden Gerig
#include "Graph.h"
using namespace std;
Graph::Graph(string filename){
	ifstream ifs(filename.c_str());
	int vertnum;
	ifs>>vertnum;
	for(int i=0;i<vertnum;i++) // push all vertices into the vertex vector before assigning the in and out list
	{
		Vertex *vert = new Vertex(i+1);
		vertList.push_back(vert);
	}
	int svert,evert,weit; 
	ifs>>svert; 
	while(svert!=-1)
	{
		ifs>>evert; 
		while(evert!=-1)
		{
			ifs>>weit; // one weight means one edge
			Edge *tempedge = new Edge(vertList[svert-1],vertList[evert-1],weit); // new edge
			edgeList.push_back(tempedge);				
			vertList[svert-1]->outList.push_back(tempedge);
			vertList[evert-1]->inList.push_back(tempedge);
			ifs>>evert; 
		}
		ifs>>svert; 
	}
	ifs.close();
}
Graph::~Graph(){
	for(int i = 0; i < vertList.size(); i++)
		delete vertList[i];
	for(int i = 0; i < edgeList.size(); i++)
		delete edgeList[i];
}
void Graph::PrintGraph(){//prints as an adjacency list
	for(int i = 0; i < vertList.size();++i){
		cout<<vertList[i]->getID()<<": ";
		for(int j = 0; j < vertList[i]->outList.size();++j){
			cout<<vertList[i]->outList[j]->geteVertP()->getID();
			cout<<"["<<vertList[i]->outList[j]->getWeight()<<"],";
		}
		cout<<endl;
	}
}
void Graph::dijkstra(Vertex *src)
{
	comparisons = 0;//tallies number of comparisons made
    src->d = 0;
	src->p = NULL;
	 PriorityQueue<Vertex*> pq;
	 for(int i = 0;i<vertList.size();++i){//Fill priority queue
		if(vertList[i]->getID() != src->getID()){
			vertList[i]->d = INT_MAX;
			vertList[i]->p = NULL;
		}
		pq.insertItem(vertList[i]->d, vertList[i], vertList[i]->getID());
	}
	while(!pq.isEmpty()){//Start sifting through the vertices
		Vertex* u = pq.minElement();
		pq.removeMin();
		int sz = u->outList.size();
		for(int i =0; i < sz;++i){
			int alt = u->d + u->outList[i]->getWeight();
			Vertex* evalVert = u->outList[i]->geteVertP();
			comparisons++;
			if(u->outList[i]->geteVertP()->d == INT_MAX){//relax function
					Locator repkey = pq.getLoc(evalVert->getID());
					pq.replaceKey(repkey,alt);
					evalVert->setD(alt);
					evalVert->setP(u);
				
			}
			else if(alt < u->outList[i]->geteVertP()->d){//relax function
					Locator repkey = pq.getLoc(evalVert->getID());
					pq.replaceKey(repkey,alt);
					evalVert->setD(alt);
					evalVert->setP(u);
				
			}
			
		}
	}
	comparisons += pq.getComps();//grab comparisons from priority queue
	return;
}

void Graph::printPath(Vertex *src, Vertex *end){
	if(src->getID() == end->getID())
		throw runtime_error("End and source are the same");
	dijkstra(src);//set up vertices
	Vertex* test = end;
	vector<Vertex*> vertPath;
	if(test->p == NULL)
		throw runtime_error("No path exists");
	while(test != NULL){//work backwards to find path
		vertPath.push_back(test);
		test = test->p;
	}
	for(int i = vertPath.size()-1;i > -1; --i){//start at beginning and print
		cout<<"("<<vertPath[i]->getID()<<")";
		if (i != 0){
			int distance = vertPath[i-1]->d - vertPath[i]->d;
			cout<<"--"<<distance<<"-->";
		}
	}
	cout<<"\n Total Weight For Shortest Path: "<<end->d;
	cout<<"\n Total # of Comparisons: "<<comparisons;

}