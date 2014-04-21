#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <algorithm>
#include <exception>
#include <functional>
#include <climits>
#define INFINITY LONG_MAX
using namespace std;
struct Vertex;

struct Edge{

	Vertex* dest;
	long long cost;
	Edge(Vertex* v = 0, long long c = 0.0):dest(v), cost(c){}
};

struct Vertex{

	string name;
	vector<Edge> adj;
	long long dist;
	Vertex* prev;
	int temp;
	bool done;
	Vertex(string n):name(n){
		reset();
	}
	void reset(){
		dist = INFINITY;
		prev = 0;
		temp = 0;
		done = false;
//		start_time = finish_time = 0;
	}
};

class Graph{

	public:
	Graph() {};
	~Graph();

	void addEdge(const string&, const string&, const long long& );
	void printPath(const string&) const;
	void printGraph() const;
	long long prim(const string&);

	private:
	Vertex* getVertex(const string&);
	void clearAll();
	void printPath(const Vertex&) const;
	bool isVertex(const string&) const;
	typedef map<string, Vertex*, less<string> > vmap;
	vmap vertexMap;
	Graph(const Graph &){}
	const Graph& operator=(const Graph& rhs){
		 return *this;
	}
};

Graph::~Graph(){

	for(vmap::iterator it = vertexMap.begin(); it != vertexMap.end(); it++)
		delete (*it).second;
}

Vertex* Graph::getVertex(const string& s){

	vmap::const_iterator it = vertexMap.find(s);
	if(it == vertexMap.end()){
		Vertex* v = new Vertex(s);
		vertexMap[s] = v;
		return v;
	}

	return (*it).second;
}

void Graph::addEdge(const string& s, const string& d, const long long& c){

	Vertex *u = getVertex(s);
	Vertex *v = getVertex(d);
	Edge e(v, c);
	Edge f(u, c);
	(u->adj).push_back(e);
	(v->adj).push_back(f);
}

bool Graph::isVertex(const string& s) const {

	vmap::const_iterator it = vertexMap.find(s);
	if(it == vertexMap.end()) return false;
	return true;
}

void Graph::clearAll(){

	for(vmap::iterator it = vertexMap.begin(); it != vertexMap.end(); it++)
		(*it).second->reset();
}
struct Compare{

	bool operator() (Vertex* a, Vertex* b){
		return a->dist > b->dist;
	}
};

long long Graph::prim(const string& s){
	vmap::const_iterator itr = vertexMap.find(s);
	if(itr == vertexMap.end())
		cerr<<"Source vertex not found"<<endl;

	clearAll();
	int n = vertexMap.size() - 1;
	Vertex *p = itr->second;
	vector<Vertex*> Q;
//	priority_queue<Vertex*, vector<Vertex*>, Compare> Q;
	p->dist = 0;
	for(vmap::const_iterator it = vertexMap.begin(); it != vertexMap.end(); it++)
	Q.push_back(it->second);
	long long cost = 0;

	while(!Q.empty()){

		make_heap(Q.begin(), Q.end(), Compare());
		Vertex *u = Q.front();
		u->done = true;
		pop_heap(Q.begin(), Q.end(), Compare());
		Q.pop_back();
		for(vector<Edge>::const_iterator it = u->adj.begin(); it != u->adj.end(); it++){
			Vertex *v = it->dest;
			if(!v->done && v->dist > it->cost){
				v->dist = it->cost;
				v->prev = u;
//				cout<<"cost of "<<v->name<<" is updated to "<<v->dist<<endl;
			}
		}

	}

	for(vmap::const_iterator it = vertexMap.begin(); it != vertexMap.end(); it++){
	 	cost+=it->second->dist;
	}

	return cost;
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    Graph G;
    string line;
    int n, e;
    getline(cin, line);
	stringstream str(line);
    str>>n>>e;
	while(e--){
        getline(cin, line);
		stringstream str(line);
		string u, v;
		long long c;
		str>>u>>v>>c;
//		cout<<"u = "<<u<<" v = "<<v<<" c = "<<c<<endl;
		G.addEdge(u, v, c);
		G.addEdge(v, u, c);
	}
    int t1=0, t2=0;
    cin>>t1>>t2;
    long long cost = 0;
    cost = G.prim("1");
    if(cost>0) cout<<t2<<endl;
    else cout<<t1<<endl;
    return 0;
}
