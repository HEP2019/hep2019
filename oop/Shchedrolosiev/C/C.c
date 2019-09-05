#include <iostream>
#include <cmath>
#include <stdlib.h>

int count(long int x1,long int x2,long int y1,long int y2)
{
// 	long int counts = 0;
    long int current = 0;

    if(x1==x2)
        return abs(y1-y2)-1;
    if(y1==y2)
        return abs(x1-x2)-1;
    
	if(x1<x2)
	{
        long int d_x = x2-x1;
        long int d_y = y2-y1;
    
		for(long int i=1; i<d_x/2+1; i++){
			if(i * d_y % d_x == 0)
            {
                current = i;
                break;
            }
			//counts++;
            
		}

	}
	if(x1>x2)
    {
        long int d_x = x2-x1;
        long int d_y = y2-y1;
 
        for(long int i=1; i<-d_x/2+1; i++){
			if(i * d_y % d_x == 0)
            {
                current = i;
                break;
            }
                //counts++;
    
        }        
    }
    if(current == 0)
        return 0;
    else
    {
    long int counts = abs(x1-x2)/current-1;
    return counts;
    }
        
    }

int main()
{
	long int x1,x2,y1,y2;

	std::cin>>x1;
	std::cin>>y1;

	std::cin>>x2;
	std::cin>>y2;


	std::cout<<count(x1,x2,y1,y2);

	return 0;
}
