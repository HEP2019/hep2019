#include <iostream>
#include <vector>

int power10(int power)
{
	int res =1;
	for(int k=0;k<power;k++)
	{
		res*=10;
	}
	return res;
}

void bubble_swap(std::vector<int> &digits, int start_point)
{
	int veclen = digits.size();
	int max_index = start_point;
	int start_value = digits[start_point];
	for(int i=start_point;i<veclen;i++)
	{
		if(digits[i]>digits[max_index])
		{
			max_index = i;
		}
	}
	digits[start_point]=digits[max_index];
	digits[max_index]=start_value;
}

int sorted_number(std::vector<int> &digits)
{
	int veclen = digits.size();
	for(int i=0;i<veclen;i++)
	{
		bubble_swap(digits,i);
	}
	int result = 0;
	for(int i=0;i<veclen;i++)
	{
		result+=digits[i]*power10(i);
	}
	return result;
}




int get_lowest_num(long int num)
{
	if(num<10)
	{
		return num;
	}
	std::vector<int> digits;
	for(int i=9;i>1;i--)
	{
		while( (num>0) && (num%i==0) )
		{
			digits.push_back(i);
			num/=i;
		}
	}
	if(num!=1)
	{
		return -1;
	}
	return sorted_number(digits);
}


int main()
{
	long int number;
	std::cin>>number;
	std::cout<<get_lowest_num(number);
	return 0;
}