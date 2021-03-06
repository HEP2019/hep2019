#include <iostream>
#include <string>
#include <cstdlib>

long long int euc(long long int a,long long int b) 
{ 
    if (a == 0) 
        return b; 
    return euc(b % a, a); 
}

int myAtoi(const char* str) 
{ 
    int res = 0; // Initialize result 
  
    // Iterate through all characters of input string and 
    // update result 
    for (int i = 0; str[i] != '\0'; ++i) 
        res = res * 10 + str[i] - '0'; 
  
    // return result. 
    return res; 
} 

int parse_n_calc(std::string str)
{
	long long int arr[4];
	std::string temp = "";
	int ind=0;
	for(int i = 0; i < str.size()+1; ++i) 
	{
		if( isdigit(str[i]) )
		{
			temp = temp+str[i];
		}
		else
		{
			long long int str_value = myAtoi(temp.c_str());
			if(ind>3) break;
			arr[ind]=str_value;
			ind++;
			temp = "";
		}
	}
	return euc(abs(arr[2]-arr[0]),abs(arr[3]-arr[1]) );
}

int main()
{
	std::string str1;
	getline(std::cin, str1);
	long long int result = parse_n_calc(str1)-1;
	std::cout<<result;
	return 0;
}