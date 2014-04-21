#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
using namespace std;
char open(char c){
    if(c == ')') return '(';
    if(c == '}') return '{';
    if(c == ']') return '[';
}
int fun(string s){
    stack<char> st;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == '(' || s[i] == '{' || s[i] == '[') st.push(s[i]);
        else if(s[i] == ')' || s[i] == '}' || s[i] == ']'){
            if(st.top() != open(s[i])) return false;
            st.pop();
        }
    }
    if(st.empty()) return true;
    return false;
}

int main(){

    string s;
    while(cin>>s)
    cout<<fun(s)<<endl;
}
