#include <list>
#include <iterator>
#include <iostream>
using namespace std;

main()
{
	int N;
	list<int> zn; 
	cin>>N;
	for(int i=9; i>1; i--){
		while(N%i==0){
			N/=i;
			zn.push_front(i);
		}
	}
	if(N>9){cout<<-1<<endl;}
	else{copy(zn.begin(), zn.end(), ostream_iterator<int>(cout,""));}
	cout<<endl;
}