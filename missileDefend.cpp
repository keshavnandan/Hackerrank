#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <list>
#include <cstring>
#include <string>
#include <cmath>
#include <utility>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <sstream>
#include <climits>
using namespace std;

struct missile{
    int t;
    int f;
    missile(int t = 0, int f = 0) : t(t), f(f){}
};
bool valid(const missile &n, const missile &m){
    return m.t > n.t && abs(n.f-m.f) <= m.t-n.t;
}
bool same(const missile &n, const missile &m){
    return n.f == m.f && n.t == m.t;
}
bool operator<(const missile &n, const missile &m){
    return n.t < m.t || (n.t == m.t && n.f < m.f);
}

int defend(set<missile> fired, list<missile> mlist){
        if(mlist.size() == 0) return 0;
        missile m = mlist.front();
        mlist.pop_front();
        cout<<"m: "<<m.t<<", "<<m.f<<endl;

        if(fired.empty()){
            fired.insert(m);
            int ret = defend(fired, mlist);
            cout<<"res: "<<m.t<<", "<<m.f<<" = "<<ret+1<<endl;
            return ret+1;
        }
        else{
            set<missile>::iterator it;
            for(it = fired.begin(); it != fired.end() && !valid(*it, m) && !same(*it, m); it++);
            if(it != fired.end() && valid(*it, m)){

                vector<missile> candidate;
                for(set<missile>::iterator j = it; j != fired.end(); j++)
                    if(valid(*j, m)) candidate.push_back(*j);
                fired.insert(m);
                cout<<"----candidate----"<<endl;
                for(vector<missile>::iterator j = candidate.begin(); j != candidate.end(); j++) cout<<j->t<<" : "<<j->f<<endl;
                cout<<"----candidate----"<<endl;
                int minval = INT_MAX;

                for(int k = 0; k < candidate.size(); k++){
                    missile c = candidate[k];
                    fired.erase(c);
                    int val = defend(fired, mlist);
                    if(minval > val) minval = val;
                    fired.insert(c);
                }
                int ret = min(defend(fired, mlist)+1, minval);
                cout<<"res: "<<m.t<<", "<<m.f<<" = "<<ret<<endl;
                return ret;
            }

            else {
                fired.insert(m);
                int ret = defend(fired, mlist);
                if(it == fired.end()) ret++;
                cout<<"res: "<<m.t<<", "<<m.f<<" = "<<ret<<endl;
                return ret;
            }
        }
}

int main()
{
    int n;
    cin>>n;
    list<missile> l;
    while(n--){
        int t, f;
        cin>>t>>f;
        l.push_back(missile(t, f));
    }
    set<missile> s;
    cout<<defend(s, l)<<endl;
}
