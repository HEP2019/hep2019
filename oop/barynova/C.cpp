#include <iostream>

using namespace std;

int numrob(double a, double b, int k)
{
    double nexta = a /2.0;
    double nextb = b/2.0;
    if (((int)nexta == nexta )&& ((int)nextb == nextb)){
        (k == 0) ? k=1 : k=k*2+1;
       k = numrob(nexta, nextb, k);
    }
    if ((((int)nexta != nexta ) || ((int)nextb != nextb) ) && nexta>1 && nextb>1 ){
        double kp;
        (nexta>nextb) ? kp=nexta/nextb : kp=nextb/nexta;
        if ((int)kp==kp)  (k +=(int)(kp-1)) ;
    }
    return k;
}


int main()
{
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0, a = 0, b = 0, k = 0;
    cin>> x1>>y1>>x2>>y2;
    a = y2 - y1;
    b = x2 - x1;
    if(a<0)  a*=-1;
    if(b<0)  b*=-1;
    a == 0 ? k=b-1 : k=0;
    b == 0 ? k=a-1 : k=k;
    if((x1==y1) && (x2==y2) && (x1 !=x2))   x2>x1 ? k = x2-x1-1 : k=x1-x2-1;
    if (k ==0) k = numrob(a*1.0, b*1.0, k);
    if (k <0) k*=(-1);
    k == -1 ? cout<<0<<endl : cout<<k<<endl;
}
