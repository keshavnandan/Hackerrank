#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <numeric>
using namespace std;
map<int, int> M;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t, N, m;
    int x, y, z, v, x1, y1, z1;
    string s;
    cin>>t;
    while(t--){
        M.clear();
        cin>>N>>m;
        while(m--){
            cin>>s;
            if(s == "UPDATE"){
                cin>>x>>y>>z>>v;
                x--; y--; z--;
                M[x + N*y + N*N*z] = v;
            }
            else{
                cin>>x>>y>>z>>x1>>y1>>z1;
                long sol = 0;
                for(map<int, int>::iterator it = M.begin(); it != M.end(); it++){
                    int k = it->first;
                    int xx = k%N, yy = (k/N)%N, zz = (k/(N*N)), vv = it->second;
                    xx++; yy++; zz++;
//                    cout<<"["<<xx<<" "<<yy<<" "<<zz<<"] = "<<vv<<endl;
                    if(x <= xx && xx <= x1 && y <= yy && yy <= y1 && z <= zz && zz <= z1)
                    sol += vv;
                }
                cout<<sol<<endl;
            }
        }
    }
    return 0;
}
