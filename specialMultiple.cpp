#include <iostream>
#include <cmath>
using namespace std;
long long mat[1000005];
int bitw = 18;
int main(){

    for(int i = 1; i <= (1<<bitw); i++){
        long long num = 0;
        for(int j = 0; j <= bitw; j++)
            if(((1<<j)&i)) num += pow(10, j);
        mat[i] = num;
//        cout<<i<<" "<<num<<endl;
    }
//    for(int i = 1; i <= (1<<10); i++) cout<<i<<" "<<mat[i]<<endl;
    int n, t;
    cin>>t;
    while(t--){
        cin>>n;
        if(n % 3 == 0) n = n/3;
        if(n % 3 == 0) n = n/3;
        for(int i = 1; i <= (1<<bitw); i++){
            if(mat[i] % n == 0){
                cout<<9*mat[i]<<endl;
                break;
            }
        }
    }
}
