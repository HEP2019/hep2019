#include <iostream>

struct Data
{
	char c1;
	int x;
	char c2;
	short y;
};

int main()
{
	std::cout << sizeof(Data);
	return 0;
}
