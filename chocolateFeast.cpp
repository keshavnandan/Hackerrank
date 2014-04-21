#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <utility>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <sstream>
using namespace std;

int main()
{
    int n, m, c;
    int t;
    cin>>t;
    while(t--){
        cin>>n>>c>>m;
        int res = 0;
        int nc = n/c, nw = nc;
        while(nc){
            res += nc;
            nc = nw/m;
            nw = nw%m+nc;
        }
        cout<<res<<endl;
    }
}


