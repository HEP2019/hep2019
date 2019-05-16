#include <iostream>

using namespace std;

int main()
{
    
    int D=1000000007;
    unsigned long long  C=1;
    unsigned long long hash=0;
    string st;
    cin>> st;
    for (int i=0; i< st.length();i++)
    {
        hash=(hash+(int)st[i]*C)%D;
        C=(C*1009)%D;
    }
    cout<<hash%D;
}

