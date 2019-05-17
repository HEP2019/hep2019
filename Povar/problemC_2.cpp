#include <iostream>
using namespace std;

long int gcd(long int a, long int b)
{
    if (a<0) a*=-1;
    if (b<0) b*=-1;
    if(b == 0)
        return a;
    else
        return gcd(b, a%b);
}

int main()
{
    long int x1, y1, x2, y2, dx, dy;
    
    cin >> x1 >> y1 >> x2 >> y2;
    dx=x1-x2;
    dy=y1-y2;
    cout << gcd(dx, dy) - 1;
    return 0;
    
}
