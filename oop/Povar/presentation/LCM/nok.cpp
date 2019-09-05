#include <iostream>

using namespace std;
int euclid_algo(int, int);//прототип функции нахождения наибольшего общего делителя
int lcm (int, int);//прототип функции наименьшего общего кратного
int main()
{
    int a, b;
    cout << "Enter a:";
    cin >> a;
    cout << "Enter b:";
    cin >> b;
    cout << "Your NOK is:" << lcm(a,b) << endl;
    return 0;
}
int euclid_algo(int arg1, int arg2){//определение функции наибольшего общего делителя
    if (arg2==0){
        return arg1;
    }
    else
        return euclid_algo(arg2,arg1%arg2);
}
int lcm (int arg1, int arg2) {// определение функции наименьшего общего кратного
    return arg1 / euclid_algo (arg1, arg2) * arg2;
}
