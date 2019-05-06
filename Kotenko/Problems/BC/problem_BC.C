#include <cmath>
#include <iostream>

#define ARRAYLEN 82

void add_shifted_array(int* base_array, int* array_toadd, int ax_ar_len)
{
	for(int shift = 1; shift<10; shift++)
	{
		for(int i=0;i<ax_ar_len;i++)
		{
			base_array[shift+i]+=array_toadd[i];
		}
	}
}

void BogdanFuncValues(int* values_array)
{
	int axil_array_length =10;

	for(int power = 1;power<9;power++)
	{
		int* axil_array = new int[axil_array_length];
		for(int i=0;i<axil_array_length;i++)
		{
			axil_array[i]=values_array[i];
		}
		add_shifted_array(values_array,axil_array,axil_array_length);

		delete []axil_array;
		axil_array_length+=9;
	}
}


int main()
{
	int point;
	std::cin>>point;
	int digitsum_array[ARRAYLEN];

	for(int i=0;i<10;i++)
	{
		digitsum_array[i]=1;
	}
	for(int i=10;i<ARRAYLEN;i++)
	{
		digitsum_array[i]=0;
	}
	BogdanFuncValues(digitsum_array);
	digitsum_array[1]+=1;

	std::cout<<digitsum_array[point];
	return 0;
}