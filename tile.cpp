#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
int num=0;
int lim=INT_MAX;
int fun(vector<string> M, pair<int, int> S, pair<int, int> D, int count, int cost){
    if(count == 0) return 0;
    if(cost>lim) return -1;
    int w  = D.first, h  = D.second;
    int sx = S.first, sy = S.second;
    if(sx < 0 || sx >= h || sy < 0 || sy >= w)  return -1;
    if(M[sx][sy] == '*'){
        count--;
        M[sx][sy] = '+';
        if(count == 0) {
//            cout<<"yoo"<<endl;
            if(lim>cost) lim=cost;
            return 0;
//            exit(0);
        }
    }

    else if(M[sx][sy] == 'x' || M[sx][sy] == '+') return -1;
    int l,r,u,d;
    l=r=u=d=INT_MAX-10;
    M[sx][sy] = '+';
//    cout<<num++<<endl;
//    for(int i=0; i<w; i++) cout<<"-";
//    cout<<endl;
//    for(int i=0; i<h; i++) cout<<M[i]<<endl;
    if(sy-1>=0 && M[sx][sy-1] != '+' && M[sx][sy-1] != 'x')
        l = fun(M, make_pair(sx, sy-1), D, count, cost+1);

    if(l!=0 && sy+1<w && M[sx][sy+1] != '+' && M[sx][sy+1] != 'x')
        r = fun(M, make_pair(sx, sy+1), D, count, cost+1);

    if(r!=0 && sx-1>=0 && M[sx-1][sy] != '+' && M[sx-1][sy] != 'x')
        u = fun(M, make_pair(sx-1, sy), D, count, cost+1);

    if(u!=0 && sx+1<h && M[sx+1][sy] != '+' && M[sx+1][sy] != 'x')
        d = fun(M, make_pair(sx+1, sy), D, count, cost+1);


    if(l == -1) l = INT_MAX-10;
    if(r == -1) r = INT_MAX-10;
    if(u == -1) u = INT_MAX-10;
    if(d == -1) d = INT_MAX-10;
//    cout<<l<<","<<r<<","<<u<<","<<d<<endl;
    int ret = min(min(l, r), min(u, d))+1;

}

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int w, h;
    pair<int,int> S,D;
    vector<string> M;
    cin>>w>>h;
    M.resize(h);
    for(int i = 0; i < h; i++) cin>>M[i];
//    for(int i=0; i<h; i++) cout<<M[i]<<endl;
    int count=0;
    for(int i=0; i<h; i++){
        for(int j=0; j<w; j++)
            if(M[i][j] == '*')  count++;
            else if(M[i][j] == 'o') S = make_pair(i,j);
    }
    D = make_pair(w,h);
//    cout<<count<<endl<<S.first<<","<<S.second<<endl;
    cout<<fun(M,S,D,count,0)<<endl;
//    cout<<num<<endl;
    return 0;
}

