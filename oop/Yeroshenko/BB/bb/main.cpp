#include <iostream>

using namespace std;

#define NNUM 35

int main()
{
    unsigned int N, div = 9;

    cin>>N;

    int container[NNUM];
    int count = 0;

    while (N>1) {
        if (div < 2){
            cout << -1;
            return 0;
        }
        while (N%div == 0) {
            container[count] = div;
            ++ count;
            N /= div;
        }
        div--;
    }

    long long answer = 0;
    for (int i = count; i > 0; --i) {
        answer = answer*10 + container[i-1];
    }

    cout << answer;
    return 0;
}
