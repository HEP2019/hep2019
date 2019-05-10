#include <iostream>

using namespace std;

int main(){
    unsigned int long N,Q = 0, pos = 1;
    cin >> N;
    if(N==0){
        cout << 10;
        return 0;
    }
    if(N == 1)
    {
        cout << N;
        return 0;
    }
    int gcd = 9;
    while(gcd > 1){
        while((N % gcd) == 0){
            Q += pos*gcd;
            pos = pos*10;
            N = N/gcd;
        }
        gcd--;
    }
    if(N>1){
        cout <<-1;
        return 0;  
    }
    cout << Q;
    return 0;
}    
