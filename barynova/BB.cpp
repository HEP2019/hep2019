#include <iostream>

using namespace std;

int main()
{

   long int N, Q = 0 ,p = 1;
   cin >> N;
   if(N==0)
    {
        cout<<"10"<<endl;
        return 0;
    }
    if(N<10)
    {
        cout<<N<<endl;
        return 0;
    }
    for(int div = 9; div > 1; --div)
    {
        while( (N%div) == 0)
        {
            Q += p * div;
            p = p * 10;
            N /= div;
        }
    }
  if(N>1)
    {
        cout<<"-1"<<endl;
        return 0;
    }
   cout << Q << endl;
    return 0;
}
