#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    unsigned int N, div = 9;
    vector<unsigned int> list(0);

    cin>>N;

    while (N>1) {
        if (div < 2){
            cout << -1;
            return 0;
        }
        while (N%div == 0) {
            list.push_back(div);
            N /= div;
        }
        div--;
    }

    sort(list.begin(), list.end(),
         [](unsigned int a, unsigned int b){return a<b;});

    unsigned int answer = 0;
    for (auto i: list) answer = answer*10 + i;

    cout << answer;
    return 0;
}
