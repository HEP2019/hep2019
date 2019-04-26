#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

int D = 1000000007;
std::vector<long int> C_v = {1};

int hesh(std::vector<char> v)
{
	long int sum = 0;
	long int C;
	for(char Ci : v){
		std::cout<<0+Ci<<"\n";
		C = C_v[C_v.size() - 1];
		sum = (sum + (C * Ci)%D)%D;
		C_v.push_back( C * 1009 % D );
	}
	return sum;
}

int main()
{
	std::string read;
	std::vector<char> text;
	std::getline(std::cin,read);
	std::copy(read.begin(),read.end(),std::back_inserter(text));

	std::cout<<hesh(text);
	return 0;
}
