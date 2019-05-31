#include <iostream>
#include <list>
#include <iterator>
using namespace std;

template <typename T>
T mynext(T iter, size_t n)
{
	std::advance(iter, n);
	return iter;
}

int main(){
	int N,K,B,C,M,A1,AI,Ai;
	list<int> res;

	cin>>N>>K>>B>>C>>M>>A1;
	Ai=A1;
	for(int i=0; i<N; i++){
		AI=(Ai*B+C)%M;
		res.push_front(Ai);
		Ai=AI;
	}
	cout << res.size() << ' ' << N << ' ' << K << ' ' << std::endl;
	res.sort();
	copy(mynext(res.begin(),N-K), res.end(), ostream_iterator<int>(cout," ")); 
	}