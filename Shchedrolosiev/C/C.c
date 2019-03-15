#include <iostream>
#include <cmath>
#include <stdlib.h>

int count(long int x1,long int x2,long int y1,long int y2)
{
	long int counts = 0;

    if(x1==x2)
        return abs(y1-y2)-1;
    if(y1==y2)
        return abs(x1-x2)-1;
    
	if(x1<x2)
	{
		for(long int i=1; i<x2-x1; i++){
			if(i * (y2-y1) % (x2-x1) == 0)
			counts++;
            
		}

	}
	if(x1>x2)
    {
        for(long int i=1; i<x1-x2; i++){
			if(i * (y2-y1) % (x2-x1) == 0)
			counts++;
    
        }        
    }
    return counts;
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
