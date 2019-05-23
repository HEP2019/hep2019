#include <iostream>
#include <map>
using namespace std;

int main(){
	int N,M,c,s;
	map<int,int> mp;

	cin>> N;
	if(N<100001 && N>-1){
	for(int i=0;i<N;i++){
		cin>>c;
		mp[c]++;
		}
	

	cin>> M;
	if(M<100001 && M>0){
		for(int j=0;j<M;j++){
			cin>>s;
			cout<<mp[s]<<" ";
			}
		}
	}
}