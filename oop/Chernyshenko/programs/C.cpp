//time limit pri 10^7
#include <iostream>
#include <cmath>
using namespace std;

int main(){
	int x1,x2,y1,y2;
	cin>>x1>>y1>>x2>>y2;
	double x,y;
	x=abs(x2-x1);
	y=abs(y2-y1);
 if(x==0 && y==0){
 	cout<<0;
 	return 0;
 }
 if(x==0 || y==0){
 	cout<<max(x,y)-1;
 	return 0;
 }
 int res=0;
 double func=min(x,y)/max(x,y);
	for(int n=1; n<max(x,y); n++){
		if(func*n==int(func*n)){
			res=max(x,y)/n-1;
			break;
		 }
		 
	}
	cout<<res<<endl;

}