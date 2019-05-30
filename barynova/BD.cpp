#include <iostream>
using namespace std;


int main ()
{
  int n, i, j, m, q=0, s=0;
  cin>>n;
  int arr[n+1][n+1];
  if (n<5 or n>500)
  {
    return 1;
  }
  for (i=0; i<n; i++)
  {
    for (j=0; j<n; j++)
    {
      if (i==j & (i==1 or i==0))
      {
        arr[i][j]=1;
      }
      else
      {
        arr[i][j]=0;
      }
    }
  }
  for (i=2;i<=n;i++)
  {
    for (j=1; j<i; j++)
    {
      s=0;
      for (m=0; m<j; m++)
      {
        s+=arr[i-j][m];
      }
      arr[i][j]=s;
    }
    arr[i][i]=1;
  }
  for (i=1; i<n; i++)
  {
    q+=arr[n][i];
  }
  cout<<q<<endl;
}
