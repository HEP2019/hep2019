#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){

    int N;
    cin>>N;

    long long int broken_serial;
    vector<long long int> broken_phones;

    for( int i=0; i<N; i++){
        cin>>broken_serial;
        broken_phones.push_back(broken_serial);
    }

    int M;
    cin>>M;

    long long int serial_number;
    map<long long int,long long int> serial_map;
    
    for(int i=0; i<M; i++){
        cin>>serial_number;    
        serial_map[serial_number]++;    
    }

    int s=0;
        for(int k=0; k<broken_phones.size(); k++){
           	if(broken_phones[k+1]!=broken_phones[k]){
                if(serial_map[broken_phones[k]]!=0) s+=serial_map[broken_phones[k]]; 
            }
     }
     cout<<s<<endl;
    return 0;
}
