#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int r, c;
    int M[51][51];
    cin>>r>>c;
    typedef pair<int, int> pi;
    set<pi> S;
    vector<pi> V;
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++){
            cin>>M[i][j];
            if(M[i][j] == 1){
                pi p = make_pair(i, j);
                S.insert(p);
                V.push_back(p);
            }
        }

    int final_cost = 1000000;
    while(!V.empty()){
        int cost = 0;
        pi p = V.back();
        cout<<p.first<<","<<p.second<<endl;
        V.pop_back();
        set<pi> A, B(S);
        A.insert(p); B.erase(p);
        while(!B.empty()){
            int temp_cost = 1000000;
            for(set<pi>::iterator it = B.begin(); it != B.end(); it++){
                pi t = *it;
                int loop_cost = 0;
                for(set<pi>::iterator jt = A.begin(); jt != A.end(); jt++){
                    pi t1 = *jt;
                    int c = max(abs(t.first-t1.first), abs(t.second-t1.second));
                    if(c > loop_cost)   loop_cost = c;
                }
                if(loop_cost < temp_cost){
                    temp_cost = loop_cost;
                    p = t;
                }
            }
            cost += temp_cost;
            A.insert(p); B.erase(p);
        }
        cout<<cost<<endl;
        if(final_cost > cost) final_cost = cost;
    }
    cout<<final_cost<<endl;
    return 0;
}
