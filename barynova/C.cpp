#include <iostream>

using namespace std;


main()
{
  int x1, y1, x2, y2, x, y, n=0;
  double tg;
  cin >> x1 >> y1 >> x2 >> y2 ;
  x = x1 - x2;
  y = y1 - y2;

  if (x==0 or y==0)
  {
    n=max(abs(x),abs(y))-1;
    if (n==-1)
    {
      cout<<0<<endl;
    }
    else
    {
      cout<<n<<endl;
    }
  }

  else
  {
    tg = max(abs(x),abs(y))/min(abs(x),abs(y));
  //  cout<<tg<<endl;
    if (int(tg)-tg==0)
    {
      n=int(tg)-1;
      cout<<n<<endl;
    }
    else
    {
      return 1;
    }
  }
}
