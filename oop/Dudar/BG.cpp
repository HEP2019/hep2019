#include <iostream>
#include <map>

using namespace std;

int main(){

    // Number of mutants in the lab
    int N;
    cin>>N;

    //Input all given color into the map
    map<int, int> colors_map;
    int color;
    for(int i=0; i<N; i++){
        cin>>color;
        colors_map[color]++;
    }

    //Number of output colors
    int M;
    cin>>M;

    //Printing asked colors
    int asked_color;
    for(int i=0; i<M; i++){
        cin>>asked_color;
        cout<<colors_map[asked_color]<<" ";
    }

    return 0;
}