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
#include <climits>
using namespace std;

int main()
{
    long long n = 0, k = 0;
    cin>>n>>k;
    vector<int> v(n);
    for(long long i = 0; i < n; i++) cin>>v[i];
    sort(v.begin(), v.end());
    long long minval= LLONG_MAX;
//    for(long long i = 0; i<n; i++) cout<<v[i]<<endl;
    for(long long i = 0; i+k<=n; i++){
        cout<<*max_element(v.begin()+i, v.begin()+i+k)<<" "<<*min_element(v.begin()+i, v.begin()+i+k)<<endl;
        int t = v[i+k-1]-v[i];
        if(t < minval) minval = t;
//        cout<<"t = "<<t<<endl;
    }
    cout<<minval<<endl;
}


