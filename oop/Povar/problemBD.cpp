#include <iostream>
#include <vector>

using namespace std;

vector <vector <bool> > b;
vector <vector <unsigned long long> > res;

unsigned long long func(int N, int h){
    
    unsigned long long result = 1;
    for (int i = h; i <= N && i + 1 <= N - i; i++)
        if (b[N - i][i + 1])
            result += res[N - i][i + 1];
        else
            result += func(N - i, i + 1);
    b[N][h] = true;
    res[N][h] = result;
    return result;
}

int main()
{
    int N;
    cin >> N;
    b.resize(N+1);
    res.resize(N+1);
    for (int i = 0 ; i <= N; i++)
    {
        b[i].resize(N+1, false);
        res[i].resize(N+1);
    }
    cout << func(N, 1) - 1;
}
