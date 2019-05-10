#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;
typedef std::vector<std::vector<int> > matr;

void print_v(matr initial){

	int width = initial.size(), height = initial[0].size();

		for(int i=0; i<height; i++){
			for(int j=0; j<width; j++){
			std::cout<<initial[j][i]<<" ";
			}std::cout<<"\n";
		}
	std::cout<<"\n";

}

matr map_picture(matr initial){
	
	int width = initial.size(),height = initial[0].size();

	matr final;
	final.resize(width-2,std::vector<int>(height-2));
	
	for (int col = 0; col < width-2; ++col) {
    	for (int row = 0; row < height-2; ++row) {
        
        final[col][row] = (initial[col][row+1] + initial[col+1][row] +\
		        		   initial[col+1][row+1] + initial[col+1][row+2] +\
		    			   initial[col+2][row+1]) / 5;
    }}

	return final;
}


int start_search(matr photo)
{
	photo = map_picture(photo);

	int width = photo.size(), height = photo[0].size();

	int radius = 0;

	for (int i = 0; i < height; ++i)
	{
	for (int j = 0; j < width; ++j)
	{
		if(photo[j][i]==1){

			int mark_1 = j;
			int mark_2 = j;
			radius = 1;

			while(photo[mark_2][i]==1) mark_2++;

			int center;
			center = (mark_1 + mark_2) / 2;		

			int i_ = i;
			// while(photo[center][i_]==1){
			// 	i_++;
			// 	radius++;
			// }

			do {
			radius++;
			i_++;
			}
			while(photo[center][i_]==1);

			//breake
			i=height;
			j=width;
		}
	}
	}

	return radius / 2;
}

int main(int argc, char** argv){

	int width,height;
	std::cin>>width>>height;

	matr photo;
	photo.resize(width,std::vector<int>(height));
    

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
	radius = start_search(photo);

	std::cout<<radius;    
    // if(radius==1)
    //     std::cout<<0;
    // else
    //     std::cout<<radius;

//	std::vector<std::vector<int>> photo2;
//	photo2.resize(width-2,std::vector<int>(height-2));
//	photo2 = map_picture(map_picture(photo));
	

	return 0;
}
