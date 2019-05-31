#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

int main(int argc, char** argv)
{

long int n;
std::vector<long int> list;
std::cin>>n;
for(int i=0; i<n; ++i){
	long int fill; std::cin>>fill;
	list.push_back(fill);}	

long int result = list[0];
long int sum = 0;
long int zero = 0;

for (int r=0; r<n; ++r) {
	sum += list[r];
	result = std::max (result, sum);
	sum = std::max (sum, zero);
}
std::cout<<result;
return 0;
}
