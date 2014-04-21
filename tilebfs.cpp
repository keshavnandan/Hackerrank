//accepted solution
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <climits>
using namespace std;

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int w, h;
    pair<int,int> S,D;
    vector<string> M;
    cin>>w>>h;
    M.resize(h);
    for(int i = 0; i < h; i++) cin>>M[i];
//    for(int i=0; i<h; i++) cout<<M[i]<<endl;
    int n=0;
    vector<pair<int,int> > L;
    vector<vector<int> > DM;
    map<pair<int,int>, int> A;
    for(int i=0; i<h; i++){
        for(int j=0; j<w; j++)
            if(M[i][j] == '*'){
                L.push_back(make_pair(i,j));
                A[make_pair(i,j)] = n++;
            }
            else if(M[i][j] == 'o') S = make_pair(i,j);
    }
    if(n==0){
        cout<<"0"<<endl;
        exit(0);
    }
    L.push_back(S);
    int sx=S.first, sy=S.second;
    M[sx][sy] = '*';
    A[S] = n++;
    DM.resize(n);
    for(int i = 0; i < n; i++) DM[i].resize(n);
    for(int i = 0; i < n; i++)
        cout<<L[i].first<<","<<L[i].second<<endl;
    cout<<L.size()<<"/"<<n<<endl;
    for(map<pair<int,int>, int>::iterator it = A.begin(); it != A.end(); it++)
        cout<<(it->first).first<<","<<(it->first).second<<" = "<<it->second<<endl;

    vector<string > P(M);
    for(int i = 0; i < L.size(); i++){
        M = P;
        int d = 0, l = A[L[i]];
        queue<pair<int,int> > Q;
        Q.push(L[i]);
        vector<vector<int> > T(h);
        for(int i = 0; i < h; i++) T[i].resize(w);
        T[sx][sy] = 0;
        while(!Q.empty()){
            int x = Q.front().first, y = Q.front().second;
            d = T[x][y];
            cout<<x<<","<<y<<"="<<d<<endl;
            Q.pop();
            d++;
            if(x+1 < h){
                T[x+1][y] = d;
                if(M[x+1][y] == '.') Q.push(make_pair(x+1,y));
                else if(M[x+1][y] == '*'){
                    Q.push(make_pair(x+1,y));
                    int m = A[make_pair(x+1,y)];
                    DM[l][m] = d;
                }
                M[x+1][y] = 'x';
            }
            if(x-1 >= 0){
                T[x-1][y] = d;
                if(M[x-1][y] == '.') Q.push(make_pair(x-1,y));
                else if(M[x-1][y] == '*'){
                    Q.push(make_pair(x-1,y));
                    int m = A[make_pair(x-1,y)];
                    DM[l][m] = d;
                }
                M[x-1][y] = 'x';
            }
            if(y+1 < w){
                T[x][y+1] = d;
                if(M[x][y+1] == '.') Q.push(make_pair(x,y+1));
                else if(M[x][y+1] == '*'){
                    Q.push(make_pair(x,y+1));
                    int m = A[make_pair(x,y+1)];
                    DM[l][m] = d;
                }
                M[x][y+1] = 'x';
            }
            if(y-1 >= 0){
                T[x][y-1] = d;
                if(M[x][y-1] == '.') Q.push(make_pair(x,y-1));
                else if(M[x][y-1] == '*'){
                    Q.push(make_pair(x,y-1));
                    int m = A[make_pair(x,y-1)];
                    DM[l][m] = d;
                }
                M[x][y-1] = 'x';
            }

        }
    }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(DM[i][j] == 0){
                    cout<<"ans = -1"<<endl;
                    exit(0);
                }
                cout<<DM[i][j]<<" ";
            }
            cout<<endl;
        }

    n--;
    int path[11] =  {0,1,2,3,4,5,6,7,8,9,11};
//    for(int i = 0; i < n; i++) cout<<path[i];
    if(n == 1){
        cout<<DM[0][1]<<endl;
        exit(0);
    }
    int sum = INT_MAX;
    do{
//        for(int i = 0; i < n; i++) cout<<path[i];
//        cout<<endl;
        int temp = 0;
        for(int i = 0; i < n; i++) temp += DM[path[i]][path[i+1]];
        if(sum>temp) sum=temp;
    }
    while(next_permutation(path, path+n));
    cout<<"ans = "<<sum<<endl;
    return 0;
}

