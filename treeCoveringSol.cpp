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
const int NUM = 200005;
using namespace std;
struct Vertex;

struct Edge{

	Vertex* dest;
	Edge(Vertex* v = 0):dest(v){}
};

struct Vertex{

	int name;
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
	int N;
	bool adj[NUM][NUM];
	Graph(int n) : N(n){
//        vertexMap.resize(n+1);
        for(int i = 0; i <= N; i++){
            vertexMap[i] = new Vertex(i);
            for(int j = 0; j <= N; j++) adj[i][j] = false;
        }
	};
	~Graph(){
        for(int i = 0; i <= N; i++) delete vertexMap[i];
	};

	void addEdge(const int, const int);
    long BFS(const int, bool);
    Vertex* bfs(Vertex*,set<Vertex*>);
	typedef vector<Vertex*> vmap;
	Vertex* getVertex(const int);
	void clearAll();
	Vertex* vertexMap[NUM];
	Graph(const Graph &){}
	const Graph& operator=(const Graph& rhs){
		 return *this;
	}
};

void Graph::clearAll(){

	for(int i = 0; i <= N; i++)
		vertexMap[i]->reset();
}

struct Compare{

	bool operator() (Vertex* a, Vertex* b){
		return a->dist > b->dist;
	}
};

long Graph::BFS(const int s, bool done = true){

	if(s > N+1){
		cerr<<"Destination vertex not found";
		exit(-1);
    }

/*  use temp field of each vertex to keep track of whether it is visited or not.	*/
	clearAll();
	for(int i = 1; i <= N; i++)
		vertexMap[i]->temp = 0;

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
		for(int i = 1; i <= N; i++){
            if(adj[u->name][i]){
                Vertex *x = vertexMap[i];
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
        for(int i = 1; i <= N; i++){
            if(adj[u->name][i]){
                Vertex *x = vertexMap[i];
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
		G.vertexMap[u][v] = true;
		G.vertexMap[v][u] = true;
	}
    long long cost = 0;
    cost = G.BFS(1);
    cout<<"cost  = "<<cost<<endl;
//    for(it = G.vertexMap.begin(); it != G.vertexMap.end(); it++) cout<<it->second->name<<"="<<it->second->dist<<endl;
    int it;
    for(int it = 1; it <= G.N && G.vertexMap[it]->dist != cost; it++);
    int S = G.vertexMap[it]->name;
    cost = G.BFS(S);
    for(int it = 1; it <= G.N && G.vertexMap[it]->dist != cost; it++);
    int D = G.vertexMap[it]->name;
    cout<<"source = "<<S<<" dest = "<<D<<endl;
    vector<int> R(n+1);
    R[1] = 1; R[2] = cost+1;
    set<Vertex*> A, B(G.vertexMap+1, G.vertexMap+G.N+1);
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
