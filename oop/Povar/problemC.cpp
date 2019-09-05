#include <iostream>
using namespace std;

int main()
{
    long int x1, y1, x2, y2, dx, dy, dmin;
    
    cin >> x1 >> y1 >> x2 >> y2;
    dx=x1-x2;
    dy=y1-y2;
    dmin=0;
    if (dx<0) dx*=-1;
    if (dy<0) dy*=-1;
    while(dx && dy)
    {
        dmin=dx%dy;
        dx=dy;
        dy=dmin;
    }
    dmin = dx | dy;
    cout << dmin - 1;
    
}
