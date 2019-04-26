#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int main()
{
    int n, result_number=0;
    bool was_breaked;
    int test = 0;
    vector<int> result;
    cin>>n;
    cout<<endl;

    if(n == 0)
    {
      cout<<0<<endl;
      return 1;  
    } 

    while(n!=1)
    {
        was_breaked=false;
        for(int i=9; i>1; i--)
        {
            if(n%i == 0)
            {
                result.push_back(i);
                n /= i;
                was_breaked=true;
                break;
            }
        }
        if(!was_breaked)
        {
            cout<<-1<<endl;
            return 1;
        }

        test++;
        if(test>10000) break;
    }

    if(result.empty())
    {
        cout<<-1<<endl;
        return 1;
    }
    
    for(int i=result.size()-1; i>=0; i--)
    {
        result_number += result[i]*pow(10, i);
    }
    cout<<result_number;
    
    return 1;
}
