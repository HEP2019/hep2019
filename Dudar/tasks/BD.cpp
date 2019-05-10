#include<bits/stdc++.h> 
using namespace std; 

int main(){
    int N; //(5<= N <= 500)
    cin>>N;

    int d[N+1][N+1];

    for(int i=0;i<N+1; i++){
        for(int j=0;j<N+1; j++) d[i][j]=0;
    }

    d[1][1] = 1;
    d[2][2] = 1;


int count = 0;
    for(int i=3; i<N+1;i++){
        for(int j=1; j<i; j++){   
            count = 0;
            for(int k=1; k<j; k++) count += d[i-j][k];
            d[i][j] = count;
        }
        d[i][i] = 1;
    }

    int answer = 0;

    for(int i=1; i<N; i++) answer+=d[N][i];
    //answer--;

    cout<<answer<<endl;
    return 0;
}