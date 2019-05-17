#include <iostream>
#include <cmath>
#include <vector>

int digit_swap(int, int, int);

int max(std::vector<int> v)
{
	int highest = v[0];

	for(int i=1;i<v.size();i++)
	{
		if(v[i]>highest) highest=v[i];
	}
	return highest;
}

void digitize(int* digits, int number)
{
	int remainder;
	int digit_index = 0;
	while(number>0)
	{
		remainder = number%10;
		digits[digit_index] = remainder;
		number/=10;
		digit_index++;
	}
}

int toint(int* digits)
{
	int result =0;
	for(int i=0;i<6;i++)
	{
		result+=digits[i]*int(pow(10,i)) ;
	}
	return result;
}


int get_nonzero_size(int* digits, int size)
{
	int nonzero_size = size;
	for(int len=size-1;len>0;len--)
	{
		if(digits[len]== 0)
		{
			nonzero_size--;
		}
		else
		{
			return nonzero_size;
		}
	}
	return 1;
}

int highest_price(int number,int permutations)
{
	int digits[6] = {0,0,0,0,0,0};
	digitize(digits,number);

	int result = digit_swap(number, get_nonzero_size(digits,6), permutations);
	return result;
}

int digit_swap(int number, int len, int permutations)
{
	if(len<2)
	{
		if(permutations%2==0)
		{
			permutations=0;
		}
		else
		{
			int kto_chitaet_tot_dibil[6]  = {0,0,0,0,0,0};;
			digitize(kto_chitaet_tot_dibil,number);
			int buff = kto_chitaet_tot_dibil[0];
			kto_chitaet_tot_dibil[0]=kto_chitaet_tot_dibil[1];
			kto_chitaet_tot_dibil[1]=buff;
			return toint(kto_chitaet_tot_dibil);
		}
	}

	if(permutations==0)
	{
		return number;
	}
	int digit_array[6]  = {0,0,0,0,0,0};;
	digitize(digit_array,number);

	int highest_digit_index = len-1;
	int highest_digit = digit_array[highest_digit_index];
	

	for(int i=highest_digit_index-1;i>=0;i--)
	{
		if( digit_array[i] > highest_digit )
		{
			highest_digit_index=i;
			highest_digit = digit_array[highest_digit_index];
		}
	}


	std::vector<int> ind_vec;
	for(int i=len-1;i>=0;i--)
	{
		if(digit_array[i]==highest_digit)
		{
			ind_vec.push_back(i);
		}
	}

	std::vector<int> sol_vec;
	for(int i=0;i<ind_vec.size();i++)
	{
		int test_array[6];
		for(int i=0;i<6;i++)
		{
			test_array[i] = digit_array[i];
		}
		int buff = test_array[ind_vec[i]];
		test_array[ ind_vec[i] ]=test_array[len-1];
		test_array[len-1]=buff;
		sol_vec.push_back(toint(test_array));
	}

	int result;
	std::vector<int> result_vec;
	for(int i=0;i<sol_vec.size();i++)
	{
		result_vec.push_back( digit_swap( sol_vec[i],len-1, permutations-1 ) );
	}
	result = max(result_vec);

	return result;
}

int main()
{
	int N,K;
	std::cin>>N>>K;
	int val = highest_price(N,K);
	std::cout<<val;
	return 0;//val;
}