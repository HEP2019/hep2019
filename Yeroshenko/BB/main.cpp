#include <iostream>
#include <vector>

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

    unsigned int answer = 0;
    for (unsigned int i = list.size(); i > 0; --i) {
        answer = answer*10 + list[i-1];
    }

    cout << answer;
    return 0;
}
