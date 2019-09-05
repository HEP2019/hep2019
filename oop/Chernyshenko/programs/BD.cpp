#include <iostream>
using namespace std; 

int main(){
    int n;
    cin>>n;
if(n>4 && n<501){

unsigned long long  d[n+1][n+1];
unsigned long long  cnt = 0, res = 0;
	for(int i=0;i<n+1; i++){
        for(int j=0;j<n+1; j++) {
        	d[i][j]=0;
        }
    }
    d[1][1] = 1;
    d[2][2] = 1;

for(int i=3; i<n+1; i++) {
	for(int j=2; j<i; j++) {
		cnt = 0;
		for(int k=1; k<j; k++) {
			cnt += d[i-j][k];
		}
		d[i][j] = cnt;
	}
	d[i][i] = 1; 	
}

for(int i = 1; i<n; i++) {
	res += d[n][i];
}

cout<<res<<endl;
}
}