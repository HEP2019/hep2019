#include<bits/stdc++.h> 
using namespace std; 
  
// A lookup table used for memorization 
unsigned long long int lookup[15][90]; 
  
// Memorization based implementation of recursive function 
unsigned long long int countRec(int n, int sum) 
{ 
    // Base case 
    if (n == 0) return sum == 0; 
  
    // If this subproblem is already evaluated, return the evaluated value 
    if (lookup[n][sum] != -1) return lookup[n][sum];
  
    // Initialize answer 
    unsigned long long int ans = 0; 
  
    // Traverse through every digit and recursively count numbers beginning with it 
    for (int i=0; i<10; i++) 
    if (sum-i >= 0) ans += countRec(n-1, sum-i);
    return lookup[n][sum] = ans;
} 
  
// It explicitly handles leading digit and calls countRec() for remaining n. 
unsigned long long int finalCount(int n, int sum){ 
    // Initialize all entries of lookup table 
    memset(lookup, -1, sizeof(lookup));
  
    // Initialize final answer 
    unsigned long long int ans = 0; 
  
    // Traverse through every digit from 1 to 9 and count numbers beginning with it 
    for (int i = 1; i <= 9; i++) 
    if (sum-i >= 0) ans += countRec(n-1, sum-i); 
    return ans; 
} 
  
int Bohdan_function(int S){
    int func_value=0;
    for(int n=1; n<10;n++) func_value += finalCount(n, S);
    if(S==1) func_value++;
    return func_value;
}

int main(){
    int S;
    cin>>S;
    cout<<Bohdan_function(S)<<endl;
    return 0;
}