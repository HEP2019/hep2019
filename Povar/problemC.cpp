#include <iostream>
using namespace std;

int main()
{
    long int x1, y1, x2, y2, dx, dy, dmin;
    
    cin >> x1 >> y1 >> x2 >> y2;
    dx=x1-x2;
    dy=y1-y2;
    if (dx<0) dx*=-1;
    if (dy<0) dy*=-1;
    dmin=dx;
    if (dx < dy)
    {
        dmin=dy;
        dy=dx;
        dx=dmin;
    }
    for (long int i=dy; i>0;i--) {
        if( (dx%i == 0) && (dy%i==0)){
            dmin=i;
            break;
        }
    }
    cout << dmin - 1;
    return 0;
    
}
