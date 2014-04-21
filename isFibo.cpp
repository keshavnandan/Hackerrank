#include <iostream>
#include <cmath>
#include <numeric>
#include <climits>
using namespace std;
// A utility function that returns true if x is perfect square
bool isPerfectSquare(long long x)
{
    long long s = sqrt(x);
    return (s*s == x);
}

// Returns true if n is a Fibinacci Number, else false
bool isFibonacci(long long n)
{
    // n is Fibinacci if one of 5*n*n + 4 or 5*n*n - 4 or both
    // is a perferct square
    return isPerfectSquare(5*n*n + 4) ||
           isPerfectSquare(5*n*n - 4);
}

// A utility function to test above functions
int main(){

    int long long n = 1;
    double x = 1;
    x = pow(2, 69);
    n = n<<63;
    cout<<sizeof(n)<<INT_MAX<<endl<<x<<endl;
    int t;
    cin>>t;
    while(t--){
        cin>>n;
        isFibonacci(n)? cout<<"IsFibo\n":
                         cout<<"IsNotFibo\n" ;
    }
  return 0;
}
