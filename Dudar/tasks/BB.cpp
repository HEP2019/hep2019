#include <iostream>
#include <vector>
using namespace std;

main()
{
    int n;
    bool was_breaked;
    int test = 0;
    vector<int> result;
    cout<<"Enter input Number"<<endl;
    cin>>n;
    cout<<endl;

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
            cout<<"-1"<<endl;
            return 1;
        }

        test++;
        if(test>10000) break;
    }

    if(result.size() == 0)
    {
        cout<<"-1"<<endl;
        return 1;
    }
    for(int i=result.size()-1; i>=0; i--) cout<<result.at(i);
    cout<<endl;
    return 1;

}
