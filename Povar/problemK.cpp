#include <iostream>
#include <vector>


using namespace std;

int main()
{
    int long N,K,B,C,M,A1,Ai1,Ai,X;
    cin>>N>>K>>B>>C>>M>>A1;
    vector <int long> mn(K);
    Ai1=A1;
    for(int long i=2;i<N; i++){
        Ai=(Ai1*B+C)%M;
        Ai1=Ai;
        for(int long j=0;j<K;j++){
            if(Ai > mn[j])
            {
                X=Ai;
                Ai=mn[j];
                mn[j]=X;
                
            }
        }
    }
    for(int long i=K-1;i>=0;i--){
        cout << mn[i]<<" ";
    }
    return 0;
}
