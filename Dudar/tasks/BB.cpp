#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int main()
{
    int n;
    cin>>n;

    vector <int> result;

    if(n == 0 || n == 1){
        cout<<n<<endl;
        return 0;
    }

    for(int i=9; i > 1; i--){
        while(n%i==0){
            result.push_back(i);
            n/=i;
        }
    }

    if(n>9){
        cout<<-1;
        return 0;
    }

    for(int i=result.size()-1; i>=0; i--) cout<<result[i];
    cout<<endl;
    return 0;
}