#include <iostream>
#include <cmath>

int min_h(int n){
    // Calculate minimum height of n-kubes piramid
    return (int)((sqrt(n*8-1.0)-1)/2);}

int main(int argc, char** argv){
    
    int N;
    std::cin>>N;

    unsigned long long int** array;
    array = new unsigned long long int* [N];
    for(int i = 0; i <N; i++){
        array[i] = new unsigned long long int[N];
        for(int j = 0; j <N; j++)
            array[i][j] = 0;}

    // Initial matrix 2xN
    array[0][0] = 1;
    array[0][1] = 0;
    for(int j = 1; j < N; j++){
        for(int i = 0; i<2; i++)
            array[j][i] = 1;}

    for(int i = 2; i < N; i++){
        for(int j = min_h(i); j < i; j++){
            array[j][i] = array[j-1][i-j-1] + array[j-1][i];}

        array[i][i] = array[i-1][i] + 1;

        for(int j = i + 1; j < N; j++){ 
            array[j][i] = array[j-1][i];}}

    // For debug (place in loop)
    // std::cout <<"2s"<< i+1 << " " << i+1 << " " << array[i][i] << "\n"; 

    std::cout << array[N-1][N-1] - 1 << "\n";

    for (int i = 0; i < N; i++){
          delete [] array[i];
        }
    delete [] array;
    
    return 0;
}
