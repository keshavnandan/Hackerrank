#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool isSumPossible(vector<int> a, int N){
    int n = a.size();
    if(n <= 1) return false;
    for(int i = 0; i < n-1; i++)
    for(int j = i+1; j < n; j++)
    if(a[i]+a[j] == N) return true;
    return false;

}

int main(){

    vector<int> v;
    int n, t;
    cin>>n;
    for(int i = 0; i < n; i++){
        cin>>t;
        v.push_back(t);
    }
    cin>>n;
    cout<<isSumPossible(v, n)<<endl;

}
