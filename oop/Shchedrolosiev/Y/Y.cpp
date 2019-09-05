#include <stdio.h>
#include <string.h>
#include <vector>
#include<iostream>

int base;

int add(int a, int b)
{
	int res = a;
	int res2 = b;
	while(true){
		int res_ = res;
		int res2_ = res2;
		res = (res_ + res2_) % base;
		res2 = (res_ + res2_) / base;
		if(res2==0) return res;
	}	
}	

std::vector<int> change_form(std::vector<char> input)
{	
	int n = input.size();
	std::vector<int> res(n);
	for(int i=0; i < n; ++i){
		int var = (int)input[i];
		if(var <= 57) res[i] = var - 48; 
		else if(var <= 90) res[i] = var - 65 + 10;
		else res[i] = var - 97 + 10;
	}
	return res;
}

template <class T> const T& max (const T& a, const T& b) {
  return (a<b)?b:a;     // or: return comp(a,b)?b:a; for version (2)
}

bool check(std::vector<int> init)
{
	int n = init.size();
	int res = 0;
	for(int i=0; i<n; ++i){
		res = add(init[i],res);			
	}
	//std::cout<<"res: "<<res<<"\n";
	if(res==base-1 || res==0) return true;
	else return false;
}

int trans(std::vector<int> init)
{
	int n = init.size();
	int res = 0;
	int power = 1;
	for(int i=n-1; i>=0; --i){
		res = init[i]*power;
		power = power*base;
	}
	return res;
}

int maxAt(std::vector<int>& vector_name) {
    int max = 0;
    int n = vector_name.size();
    for(int i = 0; i<n; ++i) {
         if (max < vector_name[i]) max = vector_name[i];
    }
    return max;
}

int main()
{
	std::string str;
	std::getline(std::cin, str);
	std::vector<char> number(str.begin(), str.end());
	
	std::vector<int> norm_form = change_form(number);

	int start_base = maxAt(norm_form);
	int start_base_ = 2;
	start_base = max(start_base,start_base_);

	int res;
	for(int i = start_base+1; i<=36; ++i){

		base = i;
		
		//std::cout<<"base: "<<base<<" ";
		if(check(norm_form)==true){
			std::cout<<base;
			return 0;
			break;
		}
	}
	//std::cout<<"\n";

	//std::cout<<trans(norm_form)<<"\n";
       
	//for(int i=0 ; i<norm_form.size() ; i++) std::cout << norm_form[i] << "\n";

//	std::cout<<base;
	std::cout<<"No solution.";
	return 0;
}
