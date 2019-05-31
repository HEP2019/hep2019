#include <iostream>

using namespace std;

int main()
{
    
    int k;
    int kmin = 2;
    int kmax = 36;
    char c;
    int res[37];
    for (k=2; k<=36; k++)
        res[k] = 0;
    string numberst;
    
    cin >> numberst;
    
    for (int i = 0; i < numberst.length(); i++)
    {
        c=numberst[i];
        for (k=kmin; k<=kmax; k++)
        {
            int a = 0;
            if ( c >= 'A' && c<= 'Z')
                a = c - 'A' + 10;
            if ( c >= '0' && c<= '9')
                a = c - '0';
            if ( a > kmin - 1 ) kmin = a + 1;
            res[k] = (res[k]*k + a)%(k-1);
        }
    }
    for (k=kmin; k<=kmax; k++)
        if (res[k] == 0) break;
    if (k<=36)
        cout<<k<<endl;
    else
        cout<<"No solution.";
}

