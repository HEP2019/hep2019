#include <iostream>
using namespace std;

int sum(int q)
{
  int sum=0;
  while (q!=0)
  {
      sum += q%10;
      q /= 10;
  }
  return sum;
}

main()
{
  int n=1000000000, s, i, p=0;
  cin>>s;
  if (s<1 or s>81)
  {
    return 1;
  }
  for (i=1;i<=n;i++)
  {
    
      if (sum(i)==s){p++;}
  }
  cout<<p<<endl;
}
