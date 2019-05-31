#include <iostream>
#include <map>
using namespace std;


int main()
{
    
    long int N, K, N_brac;
    long long int number;
    map<long int, long int> Serial_number;
    cin >> N;
    for (long int i=0; i<N; i++)
    {
        cin >> number;
        ++Serial_number[number];
    }
    cin >> K;
    N_brac=0;
    for(long int i=0; i < K; ++i)
    {
        cin>>number;
        if (Serial_number[number] != 0) N_brac=N_brac+1;
    }
    
    cout<<N_brac;
    return 0;
}
