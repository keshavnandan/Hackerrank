#include<iostream>
using namespace std;
int isIntegerPalindrome(int a){
    if(a/10 == 0) return 1;
    string s;
    while(a){
        int k = a%10;
        a = a/10;
        char c = '0'+k;
        s.push_back(c);
    }
//    cout<<s<<endl;
    int n = s.size();
    string s1 = s.substr(0, n/2), s2 = s.substr((n+1)/2, n/2);
    s2 = string(s2.rbegin(), s2.rend());
//    cout<<s1<<" "<<s2<<endl;
    return s1 == s2 ? 1 : 0;
}

int main(){
    int n;
    while(cin>>n)
    cout<<isIntegerPalindrome(n)<<endl;
}
