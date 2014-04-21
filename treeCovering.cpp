#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <exception>
#include <functional>
#include <climits>
#define INFINITY LONG_MAX
using namespace std;
struct Vertex;

struct Edge{

	Vertex* dest;
	Edge(Vertex* v = 0):dest(v){}
};

struct Vertex{

	int name;
	vector<Edge> adj;
	long long dist;
	Vertex* prev;
	int temp;
	bool done;
	Vertex(int id):name(id){
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
	Graph(int n) {
        vertexMap.resize(n+1);
        for(int i = 0; i <= n; i++) vertexMap[i] = new Vertex(i);
	};
	~Graph();

	void addEdge(const int, const int);
	void printGraph() const;
    long BFS(const int, bool);
    Vertex* bfs(Vertex*,set<Vertex*>);
	typedef vector<Vertex*> vmap;
	Vertex* getVertex(const int);
	void clearAll();
	vmap vertexMap;
	Graph(const Graph &){}
	const Graph& operator=(const Graph& rhs){
		 return *this;
	}
};

Graph::~Graph(){

	for(vmap::iterator it = vertexMap.begin(); it != vertexMap.end(); it++)
		delete *it;
}

Vertex* Graph::getVertex(const int s){

    if(s>vertexMap.size()+1){
        cerr<<"vertex out of range";
        exit(-1);
    }
}

void Graph::addEdge(const int s, const int d){

	Vertex *u = vertexMap[s];
	Vertex *v = vertexMap[d];
	Edge e(v);
	Edge f(u);
	(u->adj).push_back(e);
	(v->adj).push_back(f);
}

void Graph::clearAll(){

	for(vmap::iterator it = vertexMap.begin(); it != vertexMap.end(); it++)
		(*it)->reset();
}
struct Compare{

	bool operator() (Vertex* a, Vertex* b){
		return a->dist > b->dist;
	}
};

long Graph::BFS(const int s, bool done = true){

	if(s > vertexMap.size()+1){
		cerr<<"Destination vertex not found";
		exit(-1);
    }

/*  use temp field of each vertex to keep track of whether it is visited or not.	*/
    if(done)
	clearAll();
	for(vmap::iterator it = vertexMap.begin(); it != vertexMap.end(); it++)
		(*it)->temp = 0;

	Vertex* v = vertexMap[s];
	long level = 0L;
	v->dist = level;
	v->temp = 1;
	cout<<"Source vertex "<<v->name<<" is visited"<<endl;

	queue<Vertex*> Q;
	Q.push(v);
	while(!Q.empty()){
		Vertex* u = Q.front();
		Q.pop();
		if(u->prev != NULL)
		cout<<"Edge <"<<u->prev->name<<","<<u->name<<"> is traversed"<<endl;

		for(vector<Edge>::const_iterator it = u->adj.begin(); it != u->adj.end(); it++){
			Vertex *x = it->dest;
			if(x->temp == 0){
				x->temp = 1;
			    x->dist = u->dist + 1L;
			    if(x->dist > level) level = x->dist;
				x->prev = u;
				cout<<"Vertex "<<x->name<<" is visited at level "<<x->dist<<endl;
				Q.push(x);
//				cout<<x->name<<" is pushed onto queue"<<endl;
			}
		}
	}
	return level;
}

Vertex* Graph::bfs(Vertex* v, set<Vertex*> S){
    long max_depth = 0L;
    Vertex* solv = v;
    v->dist = 0L;
    cout<<"query vertex is "<<v->name<<endl;
    for(set<Vertex*>::iterator it  = S.begin(); it != S.end(); it++) (*it)->temp = 1;

    queue<Vertex*> Q;
    Q.push(v);
    while(!Q.empty()){
        Vertex *u = Q.front();
        Q.pop();
        for(vector<Edge>::const_iterator it = u->adj.begin(); it != u->adj.end(); it++){
			Vertex *x = it->dest;
			if(x->temp != -1 && x->temp != 0){
				x->temp = 0;
			    x->dist = u->dist + 1L;
			    if(x->dist > max_depth){
                    max_depth = x->dist;
                    solv = x;
                }
				x->prev = u;
				cout<<"Vertex "<<x->name<<" is visited at depth "<<x->dist<<endl;
				Q.push(x);
				cout<<x->name<<" is pushed onto queue"<<endl;
			}
		}
    }
    return solv;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    string line;
    int n, e;
    getline(cin, line);
	stringstream str(line);
    str>>n;
    cout<<"n = "<<n<<endl;
    e=n-1;
    Graph G(n);
	while(e--){
        getline(cin, line);
		stringstream str(line);
		int u, v;
		str>>u>>v;
		cout<<"u = "<<u<<" v = "<<v<<endl;
		G.addEdge(u, v);
		G.addEdge(v, u);
	}
    long long cost = 0;
    cost = G.BFS(1);
    cout<<"cost  = "<<cost<<endl;
    Graph::vmap::iterator it;
//    for(it = G.vertexMap.begin(); it != G.vertexMap.end(); it++) cout<<it->second->name<<"="<<it->second->dist<<endl;
    for(it = G.vertexMap.begin(); it != G.vertexMap.end() &&  (*it)->dist != cost; it++);
    int S = (*it)->name;
    cost = G.BFS(S);
    for(it = G.vertexMap.begin(); it != G.vertexMap.end() &&  (*it)->dist != cost; it++);
    int D = (*it)->name;
    cout<<"source = "<<S<<" dest = "<<D<<endl;
    vector<int> R(n+1);
    R[1] = 1; R[2] = cost+1;
    set<Vertex*> A, B(G.vertexMap.begin(), G.vertexMap.end());
    for(Vertex* v = G.vertexMap[D]; v != NULL; v = v->prev){
        A.insert(v);
        B.erase(v);
        v->temp = -1;
    }
    int counter = 2;

    while(A.size() < n){
        cout<<"size of A is \t"<<A.size()<<endl;
        long curr_max=0L;
        Vertex *s, *d;
        pair<Vertex*, Vertex*> curr_path;
            for(set<Vertex*>::iterator it  = A.begin(); it != A.end(); it++){
                s = *it;
                d = G.bfs(s, B);
                if(curr_max < d->dist){
                    curr_max = d->dist;
                    curr_path = make_pair(s, d);
                }
            }
//        if(curr_max)
        counter++;
        R[counter] = R[counter-1]+curr_max;
        cout<<"curr_max is "<<curr_max<<endl;
        cout<<"path from "<<curr_path.first->name<<" to "<<curr_path.second->name<<" is added to A"<<endl;
        for(Vertex* v = curr_path.second; v != curr_path.first; v = v->prev){
            A.insert(v);
            B.erase(v);
            v->temp = -1;
        }
    }
    for(int i = counter+1; i <= n; i++) R[i] = R[i-1];
    for(int i = 1; i <= n; i++) cout<<R[i]<<endl;
    return 0;
}
