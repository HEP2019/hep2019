#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){

    // N of broken numbers
    int N;
    vector<long long int> broken_phones;
    cin>>N;

    long long int broken_serial;
    for( int i=0; i<N; i++){
        cin>>broken_serial;
        broken_phones.push_back(broken_serial);
    }

    //All serial numbers
    //Number of broken serial numbers
    int M;
    cin>>M;

    long long int serial_number;
    map<long long int,long long int> serial_map;
    //Printing N of broken serial numbers
    for(int i=0; i<M; i++){
        cin>>serial_number;    
        serial_map[serial_number]++;    
    }
//
    int s=0;
        for(int k=0; k<broken_phones.size(); k++){
           // for(int j=0; j<N; j++){
                if(serial_map[broken_phones[k]]!=0) s+=serial_map[broken_phones[k]];
             //       }
     }
     cout<<s<<endl;
    return 0;
}
