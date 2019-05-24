#include <iostream>
#include <map>

using namespace std;

int main(){

    // N of serial numbers
    int N;
    cin>>N;

    //All serial numbers
    map<long long int,long long int> serial_map;
    long long int serial_number;
    for(int i=0; i<N; i++){
        cin>>serial_number;
        serial_map[serial_number]++;
    }

    //Number of broken serial numbers
    int M;
    cin>>M;

    //Printing N of broken serial numbers
    long long int broken_serial;
    int result=0;
    for(int i=0; i<M; i++){
        cin>>broken_serial;
        if(serial_map[broken_serial]>0) result++;
    }
    cout<<result<<endl;
    return 0;
}