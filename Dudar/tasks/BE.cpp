/*Moon
1)Enter 2d array
2) Find max radius for every hit with 4 neighbors.
3) Write max radius writing algorithm
4) Pick the largest radius

*/

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

class Pixel{
    public:
        int x, y, color, r_max_possible, r_moon;

    Pixel(int x0, int y0, int col){
        x = x0;
        y = y0;
        color = col;
        r_moon = 0;
    }
    
    bool operator > (const Pixel& pix) const{
        return (r_max_possible > pix.r_max_possible);
    }

    int distance_to(Pixel& pix){
        return sqrt((x-pix.x)*(x-pix.x)+(y-pix.y)*(y-pix.y));
    }

};

int main(){
    int width, height;
    cin>>width>>height; //([1, 200] both)
    vector<Pixel> dark_pixels;
    vector<Pixel> light_pixels;

    //Input of image from terminal
    string line;
    for(int str=0; str<height; str++){
        cin>>line;
        for(int pix=0; pix<width; pix++){
            if(line[pix] == '*') {light_pixels.push_back(Pixel(pix, str, 1));}
            else {dark_pixels.push_back(Pixel(pix, str, 0));}
        }
        line.erase(line.begin(), line.end());
    }

    //Input:
    // for(int h=0; h<height; h++){
    //     for(int w=0; w<width; w++){
    //         pixels.push_back(Pixel(w, h, 0));
    //     }
    // }

    for(int i = 0; i< light_pixels.size(); i++){
        light_pixels[i].r_max_possible = min(min(light_pixels[i].x, light_pixels[i].y), min(width-1-light_pixels[i].x,height-1-light_pixels[i].y));
    }

    sort(light_pixels.begin(), light_pixels.end(), greater<Pixel>());

    int R;
    bool max_exceeded=false;
    for(int i = 0; i< light_pixels.size(); i++){
        for(int p = 0; p < i; p++){
            if(light_pixels[p].r_moon>light_pixels[i].r_max_possible) max_exceeded = true;
        }
        if(max_exceeded) break;
        R = 999;
        for(int j = 0; j< dark_pixels.size(); j++){
            R = min(R, light_pixels[i].distance_to(dark_pixels[j]));
        }
        light_pixels[i].r_moon = min(R, light_pixels[i].r_max_possible);
    }

    int result=0;
    for(int i = 0; i< light_pixels.size(); i++){
        if(result < light_pixels[i].r_moon) result = light_pixels[i].r_moon;
    }
    cout<<result<<endl;
    return 0;
}