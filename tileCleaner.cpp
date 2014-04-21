#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

int fun(vector<string> M, pair<int,int> s, pair<int,int> d, int count){
        bool done=false;
        int i, j, ret = INT_MAX;
        int w = d.first, h = d.second;
        int sx=s.first, sy=s.second;
        cout<<w<<" "<<h<<" "<<sx<<" "<<sy<<" "<<count<<endl;
    if(count == 1){
        for(i = sx+1; i < h && M[i][sy] == '.'; i++);
        if(i < h && M[i][sy] == '*'){
            done = true;
            ret = min(ret, abs(i-sx));
        }
        for(i = sx-1; i >= 0 && M[i][sy] == '.'; i--);
        if(i >= 0 && M[i][sy] == '*'){
            done = true;
            ret = min(ret, abs(i-sx));
        }

        for(j = sy+1; j < w && M[sx][j] == '.'; j++);
        if(j < w && M[sx][j] == '*'){
            done = true;
            ret = min(ret, abs(j-sy));
        }
        for(j = sy-1; j >= 0 && M[sx][j] == '.'; j--);
        if(j >= 0 && M[sx][j] == '*'){
            done = true;
            ret = min(ret, abs(j-sy));
        }
        if(done)  return ret;
        return -1;
    }

        for(i = sx+1; i < h && M[i][sy] == '.'; i++);
        if(i < h && M[i][sy] == '*'){
            done = true;
            M[i][sy]  = 'o';
            M[sx][sy] = '.';
            int t = fun(M, make_pair(i,sy), d, count-1);
            ret = min(ret, abs(i-sx)+t);
            M[i][sy]  = '*';
            M[sx][sy] = 'o';
        }
        for(i = sx-1; i >= 0 && M[i][sy] == '.'; i--);
        if(i >= 0 && M[i][sy] == '*'){
            done = true;
            M[i][sy]  = 'o';
            M[sx][sy] = '.';
            int t = fun(M, make_pair(i,sy), d, count-1);
            ret = min(ret, abs(i-sx)+t);
            M[i][sy]  = '*';
            M[sx][sy] = 'o';
        }

        for(j = sy+1; j < w && M[sx][j] == '.'; j++);
        if(j < w && M[sx][j] == '*'){
            done = true;
            M[sx][j]  = 'o';
            M[sx][sy] = '.';
            int t = fun(M, make_pair(sx,j), d, count-1);
            ret = min(ret, abs(j-sy)+t);
            M[sx][j]  = '*';
            M[sx][sy] = 'o';
       }
        for(j = sy-1; j >= 0 && M[sx][j] == '.'; j--);
        if(j >= 0 && M[sx][j] == '*'){
            done = true;
            M[sx][j]  = 'o';
            M[sx][sy] = '.';
            int t = fun(M, make_pair(sx,j), d, count-1);
            ret = min(ret, abs(j-sy)+t);
            M[sx][j]  = '*';
            M[sx][sy] = 'o';
        }

        if(done)  return ret;
        return -1;


}

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int w, h;
    pair<int,int> s,d;
    vector<string> M;
    cin>>w>>h;
    M.resize(h);
    for(int i = 0; i < h; i++) cin>>M[i];
    for(int i=0; i<h; i++) cout<<M[i]<<endl;
    int count=0;
    for(int i=0; i<h; i++){
        for(int j=0; j<w; j++)
            if(M[i][j] == '*')  count++;
            else if(M[i][j] == 'o') s = make_pair(i,j);
    }
    d = make_pair(w,h);
    cout<<fun(M,s,d,count)<<endl;
    return 0;
}

