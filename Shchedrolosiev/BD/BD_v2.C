#include <algorithm>
#include <iostream>
#include <cmath>

int min_h(int n){
    // Calculate minimum height of n-kubes
    return (int)((sqrt(n*8-1.0)-1)/2) + 1;
}

int main(int argc, char** argv){
    
    int N;
    std::cin>>N;

    int** array;
    array = new int *[N];
    for(int i = 0; i <N; i++){
        array[i] = new int[N];
        for(int j = 0; j <N; j++)
            array[i][j] = 0; 
    }

    // initial point
    array[0][0] = 1; array[1][0] = 1;
    array[0][1] = 0; array[1][1] = 1;
    for(int j = 1; i < N; j++){
        for(int i = 0; i<2; i++)
            array[j][i] = 1;
    }


    for(int i = 3; i < N; i++){
        for(int j = min_h(); j < N; j++){
            
        }}

    for (int i = 0; i < N; i++){
          delete [] array[i];
        }
    delete [] array;

    
    return 0;
}
