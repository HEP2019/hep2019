#include <cstdlib>
#include <iostream>

long long BinaryExp(int base, int pow)
{
	long long res = 1;
	while (pow > 0) 
	{
	        if (pow & 1)
	            res = res * base;
	        base = base * base;
	        pow >>= 1;
        }
	return res;
};

int main()
{
	int a, b;
	std::cin>>a>>b;
	std::cout<<int(BinaryExp(a,b));
	return 0;
}
