#include <iostream>
#include <map>
#include <utility>

int main()
{
	std::map<int,int> color_map;
	int N,M;
	std::cin>>N;
	int buff;

	for(int i=0;i<N;i++)
	{
		std::cin>>buff;
		if(color_map.find(buff)==color_map.end() )
		{
			color_map.insert(std::make_pair(buff,1));
		}
		else
		{
			color_map[buff]+=1;
		}
	}
	std::cin>>M;
	for(int i=0;i<M;i++)
	{
		std::cin>>buff;
		std::cout<<color_map[buff]<<" ";
	}
	return 0;
}