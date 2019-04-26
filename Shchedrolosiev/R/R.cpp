#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

const long int D = 1000000007;
const long int C = 1009;
std::vector<long int> C_vector;


// Global function to build cofitiens vector
void fill_C(int K){
	for(int i=0; i<K-1; ++i){
		C_vector.push_back( C_vector[i] * 1009 % D );
	}
}

int hesh(std::vector<char> v)
{
	long int sum = 0;
	long int C;

	int i_end = v.size();
	for(int i=0; i<i_end; i++){
		// std::cout<<0+v[i]<<"\n";
		sum = (sum + (C_vector[i] * v[i])%D)%D;
	}
	return sum;
}

const long int A = 1103515245;
const long int B = 12345;
const long int Base = pow(2,32);
std::vector<char> string;
void fill_string(int N)
{
	long int x = 1;
	for(int i=0; i<N; ++i){
		string.push_back('a'+(x>>16)%26);
		x = (x*A + B)%Base;
	}
}

int find_hesh(int K, int Hesh)
{	
	int result = -1;
	int single_hesh;
	const int i_end = string.size()-K;
	for(int i=0; i<=i_end; ++i){
		std::vector<char> temp_hesh;
		for(int j=0; j<K; ++j){
			temp_hesh.push_back(string[i+j]);
		}
		single_hesh = hesh(temp_hesh);
		if(single_hesh==Hesh){
			result = i;
			break;
		}
	}
	return result;
}

std::vector<char> search(int N,int K,int H)
{
	fill_C(K);
	fill_string(N);
	std::vector<char> res;

	int index = find_hesh(K,H);
	if(index==-1){
		res = {0};
	}
	else {
	for(int i=index; i<index+K; ++i){
		res.push_back(string[i]);
	}
	}
	return res;
}

int main()
{
	int N, K, H;
	std::cin >> N;
	std::cin >> K;
	std::cin >> H;

	C_vector.push_back(1);

	std::vector<char> result;
	result = search(N,K,H);
	for(char a : result){
		std::cout << a;
	}

	return 0;
}
