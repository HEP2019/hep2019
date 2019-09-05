// input: N - prize, K - number of permutations
// output: max prize

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    //Input numbers
    int N, K;
    cin>>N>>K;

    //Convert number into a vector array
    vector<int> N_arr;
    while(N>0){
        N_arr.push_back(N%10);
        N/=10;
    }
    reverse(N_arr.begin(),N_arr.end());

    //If 0 pernutations return array.
    if(K == 0){
        for(vector<int>::const_iterator i = N_arr.begin(); i != N_arr.end(); i++) cout<< *i;
        return 0;
    }

    int counter = 0;
    int max_el, max_el_idx;
    int has_n_same_digits = 1;
    bool has_same_digits = false;

    //While there are permutations
    while(K>0){

        has_n_same_digits = 1;
        //If number is the largest and permutations left:
        if(counter == N_arr.size()){
            if(has_same_digits) break; 
            if(K%2 == 0) break;
            else{
                swap(N_arr[counter-1], N_arr[counter-2]);
                break;
            }
        }

        max_el = *max_element(N_arr.begin() + counter, N_arr.end());
        max_el_idx = max_element(N_arr.begin() + counter, N_arr.end()) - N_arr.begin();

        //If max digit the same which i want to swap. Skip
        if(counter == max_el_idx){
            counter++;
            continue;
        }

        for(int i = max_el_idx + 1; i<N_arr.size(); i++)
            if(N_arr[i] == max_el){
                max_el_idx = i;
                has_n_same_digits += 1;
                has_same_digits = true;
            }

        // if(has_n_same_digits > 1 && K > 1){
        //     if(has_n_same_digits == 2 && K == 2){
        //         if(N_arr[counter] > N_arr[counter+1]){
        //             swap(N_arr[counter], N_arr[max_el_idx]);

        //         }
        //     }
        //     //think where to put the rightest max digit.
        //     //it is counter if:
        //     // it is counter +1 if
        //     //...

        // }

        //Swap "counter" and max element
        swap(N_arr[counter], N_arr[max_el_idx]);
        counter++;
        K--;
    }


    //print the final number
    for(vector<int>::const_iterator i = N_arr.begin(); i != N_arr.end(); i++) cout<< *i;

    return 0;
}
/*Одинаковые цифры можно переставлять местами.*/