#include <iostream>
#include <algorithm>
using namespace std;

int main(){

    int x1, y1, x2, y2;
    cin>>x1>>y1>>x2>>y2;

    double a, b;

    double func;
    int count = 0;
    for(int x = min(x1,x2)+1; x<max(x1,x2); x++){
        func = 1.*(y2-y1)/(x2-x1)*(x-x1) + y1;
        if(func == int(func)) count++;
    }

    cout<<count<<endl;

    return 0;
}