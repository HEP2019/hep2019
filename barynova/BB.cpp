#include <iostream>
using namespace std;


main()
{
  long long int n, q=0, q1, i, p;
  cin>>n;
  if ((n<0) or (n>1000000000))
  {
    return 1;
  }
  if (n<2)
  {
    q1=n;
  }
  else
  {
    q1=-1;
    if ((n==1 and q1>=q) or (q1==-1))
    {
      q1=q;
    }

    for (i=2;i<10;i++)
    {
      if (n%i==0)
      {
  //      cout<<'n'<<n;
  //      cout<<'i'<<i;
        p=q;
        q=q*10+i;
  //      cout<<'q'<<q;
        n=n/i;
  //        cout<<'n'<<n;
        i--;
      }
    }
//    cout<<'n'<<n<<endl;
    if (n==1)
    {
      cout<<q<<endl;
    }
  }
}
