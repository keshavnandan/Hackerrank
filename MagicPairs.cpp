#include <iostream>
using namespace std;

int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		string s;
		cin>>n;
		getline(cin, s);
		cout<<(n*(n-1))/2<<endl;
	}
}
