#include <iostream>

struct Data
{
	char c1;
	char c2;
	int x;
	short y;
};

int main()
{
	std::cout << sizeof(Data);
	return 0;
}