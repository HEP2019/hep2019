#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    
    int N = 0, K=200000;
    cin >> N;
    vector<int long> X(K);
    for (int i = 0; i < N; i++){
        cin >> X[i];
    }
    int result = X[0],S = 0,Smin = 0;
    for (int j=0; j<N; ++j) {
        S += X[j];
        result =std::max(result, S - Smin);
        Smin= std::min(Smin, S);
    }
    cout << result;
    return 0;
}
