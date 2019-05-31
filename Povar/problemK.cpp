#include <iostream>
#include <vector>
using namespace std; int main() {
    int long B,C,M,A1,Ai1,Ai,X;
    int N,K;
    cin>>N>>K>>B>>C>>M>>A1;
    vector <int long> mn(K);
    Ai1=A1;
    for(int i=2;i<=N; i++){
        Ai=(Ai1*B+C)%M;
        Ai1=Ai;
        if(Ai >mn[K-1]){
            for(int  j=0;j<K;j++){
                if(Ai > mn[j]) {
                    X=Ai;
                    Ai=mn[j];
                    mn[j]=X; 
                } 
            }
        }
    }
    for(int  i=K-1;i>=0;i--){ 
        cout << mn[i]<<" "; 
    } 
    return 0; }
