#include <iostream>
#include <ctime>

using namespace std;
    unsigned int start_time =  clock();
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
int recurent(int a, int b)
{
  if (b == 0)
    cout<<a<<endl;
    //return a;
  return recurent(b, a % b);
}

int iterational(int a, int b)
{
  int t;
  while (b != 0)
  {
    t = b;
    b = a % b;
    a = t;
  }
  cout<<a<<endl;
  //return a;
}

int cycle(int a, int b)
{
  while(true)
  {
    a = a%b;
    if(a==0)
    {
      return b;
    }
    b = b%a;
    if(b==0)
    {
      cout<<a<<endl;
      //return a;
    }
  }
}

int main()
{
  int n, m, method;
  cin>>n>>m>>method;
//  unsigned int start_time =  clock();
  if (method==1) recurent(n,m);
  if (method==2) iterational(n,m);
  if (method==3) cycle(n,m);
//  unsigned int end_time = clock();
//  unsigned int search_time = end_time - start_time;
//  cout<<search_time<<endl;
}
