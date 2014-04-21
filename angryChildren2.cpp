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
    vector<long long> a(n), p(n), s(n);
    for(long long i = 0; i < n; i++) cin>>a[i];
    sort(a.begin(), a.end());
    p[0] = 0; p[1] = 0; s[0] = 0;
    for(long long i = 1; i < k; i++) p[1] += a[i];
    for(long long i = 1; i < k; i++) s[0] += (k-i)*(a[k-i]-a[i-1]);
    for(long long i = 2; i <= n-k; i++) p[i] = p[i-1]-a[i-1]+a[k+i-2];
    long long minval= s[0];
    for(long long i = 1; i <= n-k; i++) cout<<p[i]<<" ";
    cout<<endl;
    cout<<"0:"<<s[0]<<endl;
    for(long long i = 1; i <= n-k; i++){
        if(k > 2)
        s[i] = s[i-1]+(k-1)*(a[i+k-1]+a[i-1]) - 2*p[i];
        else
        s[i] = a[i+1]-a[i];
        if(s[i] < minval) minval = s[i];
            cout<<i<<":"<<s[i]<<endl;

    }

//    for(long long i = 0; i<n; i++) cout<<v[i]<<endl;
    cout<<minval<<endl;
}


