#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

void print_v(std::vector<std::vector<int> > initial){

	int width = initial.size(), height = initial[0].size();

		for(int i=0; i<height; i++){
			for(int j=0; j<width; j++){
			std::cout<<initial[j][i]<<" ";
			}std::cout<<"\n";
		}
	std::cout<<"\n";

}

std::vector<std::vector<int> > map_picture(std::vector<std::vector<int> > initial){
	
	int width = initial.size(),height = initial[0].size();

	std::vector<std::vector<int> > final;
	final.resize(width-2,std::vector<int>(height-2));
	
	for (int col = 0; col < width-2; ++col) {
    	for (int row = 0; row < height-2; ++row) {
        
        final[col][row] = (initial[col][row+1] + initial[col+1][row] +\
		        		   initial[col+1][row+1] + initial[col+1][row+2] +\
		    			   initial[col+2][row+1]) / 5;
    }}

//         print_v(final);
	return final;
}

bool check(std::vector<std::vector<int> > photo)
{
	int width = photo.size(),height = photo[0].size();
	
	int n = 0;

	for(int i=0; i<height; i++){
	for(int j=0; j<width; j++){
		if(photo[j][i] == 1)
			n++;
		if(n>=2)
			return true;
		}
	}

	return false;

}

int start_cycle(std::vector<std::vector<int> > photo)
{
	int i = 0;
	while (check(photo))
	{
		photo = map_picture(photo);
	       	i++;	
	}

	return i;
}

int main(int argc, char** argv){

	int width,height;
	std::cin>>width>>height;

	std::vector<std::vector<int> > photo;
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

	int radius;
	radius = start_cycle(photo);
    
    if(radius==1)
        std::cout<<0;
    else
        std::cout<<radius;
//	std::vector<std::vector<int>> photo2;
//	photo2.resize(width-2,std::vector<int>(height-2));
//	photo2 = map_picture(map_picture(photo));
	

	return 0;
}
