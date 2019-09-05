#include <iostream>
#include <string>

typedef long long int lli;

lli power(lli x, unsigned int y,lli p) 
{ 
    long long int res = 1;
  
    x = x % p;
    while (y > 0) 
    {
        if (y & 1) 
        {
            res = (res*x) % p;
        }
        y = y>>1;
        x = (x*x) % p;   
    } 
    return res; 
} 

lli hash(std::string str)
{
    int C=1009;
    lli D=1000000007;
    int len = str.length();
    long long int res = 0;
    for(int i=0;i<len;i++)
    {
        res+=(power(C,i,D)*(str[i]%D) )%D;
    }
    res = res%D;
    return res;
}

int main()
{
    std::string str;
    std::getline(std::cin, str);
    std::cout<<hash(str);
    return 0;
}