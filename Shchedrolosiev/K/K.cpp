#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

long int B, C, M;

template< class ForwardIterator, class T >
ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& val)
{
  ForwardIterator it;
  long int count, step;
  count = std::distance(first,last);
  while (count>0)
  {
    it = first; step=count/2;
    std::advance (it,step);
    if (!(val<*it))  
      { first=++it; count-=step+1;  }
    else count=step;
  }
  return first;
}

template< class T > const T& min (const T& a, const T& b) {
  return !(b<a)?a:b;
}

template< typename t >
void insert_sorted( std::vector<t> & vec, t const& item )
{
    vec.insert( 
    std::upper_bound( vec.begin(), vec.end(), item ),
    item);
}

template< typename t >
void insert_sorted_noresize( std::vector<t> & vec, t const& item )
{
    insert_sorted(vec, item);
    vec.erase(vec.begin());
}

template< typename t >
void func(t &A)
{
    A = (A*B + C ) % M; 
}

int main(int argc, char** argv)
{
	long int N,A;
	int K;
	std::cin>>N>>K>>B>>C>>M>>A;
	K = min(K,200);
	//std::cout<<K;
	//
	if(A>M) std::cout<<"Error: A>M\n" ;

	std::vector<long int> array;

	for(int i = 0; i<K; ++i)
	{
 		insert_sorted(array,A);
		func(A);
		std::cout<<A<<" ";
	}
	if(K<N){
	for(long int i = (long int)K; i < N; ++i)
	{
		insert_sorted_noresize(array,A);
		func(A);	
		std::cout<<A<<" ";
	}	
	}
	std::cout<<"\n";
	for (int i = 0; i < array.size(); ++i) std::cout << array[i] << " ";
	
	return 0;
}
