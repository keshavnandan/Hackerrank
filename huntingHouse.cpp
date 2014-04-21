#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;


int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    vector<vector<bool> > M;
    int n=0, budget=0, na=0;
    int cx, cy, px, py;
    vector<vector<int> > av;
    vector<int> p, d;
    cin>>budget>>n>>px>>py>>cx>>cy>>na;
    p.resize(na); av.resize(na); d.resize(na);
    M.resize(n);
    for(int i = 0; i < n; i++){
        M[i].resize(n);
        for(int j = 0; j < n; j++) M[i][j] = true;
    }
    for(int i = 0; i < na; i++) av[i].resize(2);
    string c;
    for(int i = 0; i < na; i++){
        cin>>c>>av[i][0]>>av[i][1]>>p[i]>>d[i];
        M[av[i][0]][av[i][1]] = false;
    }
    M[cx][cy] = false;
    M[px][py] = false;
/*
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            cout<<M[i][j];
        cout<<endl;
    }


    for(int i = 0; i < na; i++)
        cout<<av[i][0]<<" "<<av[i][1]<<" "<<p[i]<<" "<<d[i]<<endl;
*/
    vector<pair<int, int> > resv;
    long res = LONG_MAX, diff = LONG_MAX;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(M[i][j]){
                long rent = 0, l = 0;
                long l1 = abs(i-cx)+abs(j-cy), l2 = abs(i-px)+abs(j-py);
                l1 = abs(l1-l2);
                if(l1 < diff){

                    for(int k = 0; k < na; k++){
                        l = abs(i-av[k][0])+abs(j-av[k][1]);
                        rent += (p[k]-l*d[k])>0 ? (p[k]-l*d[k]):0;
    //                    cout<<"l = "<<l<<"\ti = "<<i<<"\tj = "<<j<<"\t"<<rent<<endl;
                    }
                    if(rent<=budget){
                        diff = l1;
                        res = rent;
                        resv.resize(0);
                        resv.push_back(make_pair(i,j));
                    }
/*                    if(rent<=budget && rent==res)
                        resv.push_back(make_pair(i,j));
                    if(rent<=budget && rent<res){
                        res = rent;
                        resv.resize(0);
                        resv.push_back(make_pair(i,j));
                    }
  */
                }
                if(l1 == diff){
                    for(int k = 0; k < na; k++){
                        l = abs(i-av[k][0])+abs(j-av[k][1]);
                        rent += (p[k]-l*d[k])>0 ? (p[k]-l*d[k]):0;
    //                    cout<<"l = "<<l<<"\ti = "<<i<<"\tj = "<<j<<"\t"<<rent<<endl;
                    }
                    if(rent<=budget && rent==res)
                        resv.push_back(make_pair(i,j));
                    else if(rent<=budget && rent<res){
                        res = rent;
                        resv.resize(0);
                        resv.push_back(make_pair(i,j));
                    }
                }
            }
        }
    }
    if(resv.size() == 0){
        cout<<"NO"<<endl;
        exit(0);
    }
    sort(resv.begin(), resv.end());
    if(resv.size() == 1){
        cout<<"("<<resv[0].first<<","<<resv[0].second<<") : "<<res<<endl;
        exit(0);
    }
/*    for(int i = 0; i < resv.size(); i++){
        cout<<resv[i].first<<" "<<resv[i].second<<endl;
    }
    cout<<res<<endl;
*/    return 0;
}
