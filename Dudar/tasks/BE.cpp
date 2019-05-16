/*Moon
1)Enter 2d array
2) Find max radius for every hit with 4 neighbors.
3) Write max radius writing algorithm
4) Pick the largest radius

*/

#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int width, height;
    cin>>width>>height; //([1, 200] both)
    int image[height][width];
    int radius_arr[height][width];

    //Input of image from terminal
    string line;
    for(int str=0; str<height; str++){
        cin>>line;
        for(int pixel=0; pixel<width; pixel++){
            //if(line[pixel] == '.') {image[str][pixel] = 0;}
            if(line[pixel] == '*') {image[str][pixel] = 1;}
            else {image[str][pixel] = 0;}
        }
        line.erase(line.begin(), line.end());
    }

    // cout<<"Input image : "<<endl;
    // for(int i=0; i<height; i++){
    //     for(int j=0; j<width; j++) cout<<image[i][j]<<" ";
    //     cout<<endl;
    // }

    int R;
    bool no_black_point_inside = true;

    for(int y0=0; y0<height; y0++){
        for(int x0=0; x0<width; x0++){
            R = 0;
            if(image[y0][x0] > 0){
                no_black_point_inside = true;
                while(no_black_point_inside){
                    R++;
                    for(int i=0; i<height; i++){
                        if(!no_black_point_inside) break;
                        for(int j=0; j<width; j++){
                            if((image[i][j] == 0 && sqrt((y0-i)*(y0-i)+(x0-j)*(x0-j)) <= R) ||
                                R > x0 || R > y0 || R > abs(width-1-x0) || R > abs(height-1-y0)){
                                R--;
                                no_black_point_inside = false;
                                break;
                            }
                        }
                    }
                }
            }
            radius_arr[y0][x0] = R;
        }
    }

    int max_R = 0;

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if(max_R < radius_arr[i][j]) max_R = radius_arr[i][j];
        }
    }
    cout<<max_R<<endl;
    return 0;
}