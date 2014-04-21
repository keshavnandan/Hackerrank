#include <iostream>
#include <algorithm>
using namespace std;

int main(){

    int n, k, t;
    int ni[505];
    cin>>t;
    while(t--){
        cin>>k;
        for(int i = 1; i <= k; i++) cin>>ni[i];
        long long sol = 0;
        int mini = 1, minv = 1000000007;
        for(int i = 1; i <= k; i++)
            if(ni[i] < minv){
                minv = ni[i];
                mini = i;
            }
        cout<<mini<<" : "<<minv<<endl;

        int a = 1, b = 1;
        for(int i = 1; i <= k; i++){
            a *= ni[i];
            b *= ni[i]-1;
        }
        sol = a-b;
        for(int i = 2; i <= minv; i++){
            long long val1 = 1, val2 = 1;
            a = 1; b = 1;
            for(int j = 1; j <= k; j++){
                a *= ni[i]-i+1;
                b *= ni[i]-i;
                val2 *= ni[j]/i;
            }
            val1 = a-b;
            cout<<i<<" "<<val1<<" "<<val2<<endl;
            sol += val2*i + (val1-val2);
        }
        cout<<sol<<endl;
    }
}
