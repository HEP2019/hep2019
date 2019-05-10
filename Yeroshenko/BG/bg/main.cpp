#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define NCOL 1000000007


int main()
{
    int N, M;

    cin >> N;

    map<int,int> colorMap;

    int color;
    for (int i = 0; i < N; ++i) {
        cin >> color;
        ++colorMap[color];
    }

    cin >> M;

    for (int i = 0; i < M; ++i){
        int col;
        cin >> col;

        cout << colorMap[col] << " ";
    }
    return 0;
}
