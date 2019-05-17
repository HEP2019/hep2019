#include <iostream>
#include <string>

typedef long long int lli;

#define TWOTOTHIRTYTWO 4294967296

lli powC(unsigned int y) 
{ 
    lli x=1009;
    lli res = 1;
   
    while (y > 0) 
    { 
        if (y & 1) 
            res = res*x; 

        y = y>>1;
        x = x*x;
    } 
    return res; 
}

lli power(lli x, unsigned int y,lli p)
{ 
    lli res = 1;
  
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
    lli C=1009;
    lli D=1000000007;
    int len = str.length();
    lli res = 0;
    for(int i=0;i<len;i++)
    {
        res+=(power(C,i,D) * (str[i]%D) )%D;
    }
    res = res%D;
    return res;
}

void fill_XN(lli* seq, int N)
{
    seq[0]=1;
    lli A=1103515245;
    lli B=12345;
    lli buff1=0;
    for(int i=1;i<N;i++)
    {
        buff1=A*(seq[i-1]%TWOTOTHIRTYTWO);
        seq[i]=(buff1+B)%TWOTOTHIRTYTWO;
    }
}

void fill_cN(lli* seq, int N, lli* xn)
{
    lli buff;
    for(int i=0;i<N;i++)
    {
        buff = xn[i];
        seq[i]='a'+(buff>>16)%26;
    }
}

int find_substring(lli* seq, int N, int K, lli hashvalue)
{
    for (int i = 0; i + K < N; i++)
    {
        if (hash(std::string(seq+i,seq+i + K)) == (hashvalue * powC(i+1)) )
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    int N,K;
    lli hashval;
    std::cin>>N>>K>>hashval;

    lli* xn_seq = new lli[N];
    fill_XN(xn_seq,N);

    lli* cn_seq = new lli[N];
    fill_cN(cn_seq, N,xn_seq);

    // for(int i=0;i<N;i++)
    // {
    //     std::cout<<xn_seq[i]<<"\t"<<char(cn_seq[i])<<"\n";
    // }
    int lowerb=find_substring(cn_seq,N,K,hashval);
    for (int i = lowerb; i < lowerb+K; i++)
    {
        std::cout<<char(cn_seq[i] );
    }
   
    delete [] xn_seq;
    delete [] cn_seq;
    return 0;
}