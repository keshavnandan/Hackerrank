#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
long long mod = 1000000007;
int fac[2000005];
int ifac[1000005];

int inv(int a) {
    long long newv = 1, old = 0, q = mod, r, h;
    int pos = 0;
    while (a > 0) {
        r = q%a;
        q = q/a;
        h = q*newv + old;
        old = newv;
        newv = h;
        q = a;
        a = r;
        pos = !pos;
    }
//    int ans = pos ? old : (mod - old);
//    return ans > 0 ? ans : -ans;
    return pos ? old : (mod - old);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t, m, n, k;

    cin>>t;
    fac[0] = fac[1] = 1;
    ifac[1] = 1;
    for(int i = 2; i <= 1000000; i++){
  //      cout<<i<<endl;
        long long x = i, y = fac[i-1];
        fac[i] = (x*y)%mod;
        x = inv(i), y = ifac[i-1];
        ifac[i] = (x*y)%mod;
    }

    for(int i = 1000001; i <= 2000000; i++){
//        cout<<i<<endl;
        long long x = i, y = fac[i-1];
        fac[i] = (x*y)%mod;
    }

//    cout<<"process complete"<<endl;
//    for(int i = 1; i < 100; i++) cout<<fac[i]<<" "<<ifac[i]<<endl;

    while(t--){

        cin>>m>>n;
        m--; n--;
        if(m == 0 || n == 0) cout<<"1"<<endl;
        else if(m == 1) cout<<n<<endl;
        else if(n == 1) cout<<m<<endl;
        else{
            long long x = fac[m+n], y = ifac[m], z = ifac[n];
            long long ans = (((x*y)%mod)*z)%mod;
            cout<<ans<<endl;
        }
    }

//    while(cin>>n>>k) cout<<nck(n, k)<<endl;

    return 0;
}
