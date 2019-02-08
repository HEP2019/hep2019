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



    for (int i = 0; i < N; i++){
          delete [] array[i];
        }
    delete [] array;

    
    return 0;
}
