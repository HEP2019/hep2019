#include <iostream>
#include <list>
#include <iterator>
using namespace std;

int main(){
	int N,K,B,C,M,A1,AI,Ai;
	list<int> res(K);

	cin>>N>>K>>B>>C>>M>>A1;
	Ai=A1;
	for(int i=0; i<N; i++){
		AI=(Ai*B+C)%M;
		res.push_front(Ai);
		Ai=AI;
	}
	res.sort();
	copy(std::next(res.begin(),N-K+1), res.end(), ostream_iterator<int>(cout," ")); 
	}