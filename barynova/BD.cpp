#include <iostream>
#include <map>
using namespace std;



int colums(int n)
{
    int totalcol = 0;
    int array1[501][501];

    for(int i = 1;i<=n;i++)
    {
        array1[i][1] = 1;
        int cols = 2;


        while (array1[i][cols]=array1[i-cols][cols]+array1[i-cols][cols-1])
        {
            if(i==n)
            {
                totalcol+=array1[i][cols];
            }
              ++cols;
        }
    }

    return totalcol;
}

int main()

{
  int N;
  cin >> N;
  cout << colums(N)<<endl;
}
