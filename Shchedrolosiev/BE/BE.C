#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

void print_v(std::vector<std::vector<int>> initial){

	int width = initial.size(), height = initial[0].size();

		for(int i=0; i<height; i++){
			for(int j=0; j<width; j++){
			std::cout<<initial[j][i]<<" ";
			}std::cout<<"\n";
		}

}

bool search_isolated(std::vector<std::vector<int>> initial){
    
    int width = initial.size(),height = initial[0].size();
    

    for(int i=1; i<height-1; i++){
        for(int j=1; j<width-1; j++){
        
            if(initial[j][i]==1)
                if(initial[j-1][i]==0)
                    if(initial[j][i-1]==0)
                        if(initial[j][i+1]==0)
                            if(initial[j+1][i]==0)
                                return 1;
    }}
    
    return 0;
    
}

std::vector<std::vector<int>> map_picture(std::vector<std::vector<int>> initial){
	
	int width = initial.size(),height = initial[0].size();

	std::vector<std::vector<int>> final;
	final.resize(width-2,std::vector<int>(height-2));
	
	for (int col = 0; col < width-2; ++col) {
    	for (int row = 0; row < height-2; ++row) {
        
        final[col][row] = (initial[col][row+1] + initial[col+1][row] +\
		        		   initial[col+1][row+1] + initial[col+1][row+2] +\
		    			   initial[col+2][row+1]) / 5;
    }}

        print_v(final);
	return final;
}


int main(int argc, char** argv){

	int width,height;
	std::cin>>width>>height;

	std::vector<std::vector<int>> photo;
	photo.resize(width,std::vector<int>(height));
    
//     for(int i=0; i<height; i++){
// 		for(int j=0; j<width; j++){
// 
// 		std::cin>>photo[j][i];
// 
// 	}}

	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
		char fill;
		std::cin>>fill;
		if ((int)fill==46)
			photo[j][i]=0;
        else
            photo[j][i]=1;
	}}

	std::vector<std::vector<int>> photo2;
	photo2.resize(width-2,std::vector<int>(height-2));
	photo2 = map_picture(map_picture(photo));
	

	return 0;
}
