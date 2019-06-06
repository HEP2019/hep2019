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
	cin>>N>>K>>B>>C>>M>>A1;
	//int l=K, d=0;
	list<int> res;

	
	Ai=A1;
	for(int i=0; i<N; i++){
		AI=(Ai*B+C)%M;
		res.push_front(Ai);
		//res.sort();
		Ai=AI;
		//d++;
		/*if(d==K){
		 res.sort();
		 cout <<d<<endl;
		 d=0;
		}*/
	}
	
	//cout << res.size() << ' ' << N << ' ' << K << ' ' << std::endl;
//	cout << sizeof res << endl;
	res.sort();
//	cout << sizeof res << endl;
	copy(mynext(res.begin(),N-K), res.end(), ostream_iterator<int>(cout," ")); 
	//copy(res.begin(), res.end(), ostream_iterator<int>(cout," ")); 
	}