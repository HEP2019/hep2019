#include <iostream>
#include <map>
#include <utility>

int main()
{
	std::map<int,int> brak_map;
	int N,K;
	std::cin>>N;
	int buff;

	for(int i=0;i<N;i++)
	{
		std::cin>>buff;
		if(brak_map.find(buff)==brak_map.end() )
		{
			brak_map.insert(std::make_pair(buff,1));
		}
		else
		{
			brak_map[buff]+=1;
		}
	}
	std::cin>>K;

	std::map<int,int> mlf_map;
	for(int i=0;i<K;i++)
	{
		std::cin>>buff;
		if(brak_map.find(buff)==brak_map.end() )
		{
			continue;
		}
		else
		{
			mlf_map.insert(std::make_pair(buff,1));
		}
	}
	int result=0;
	for(std::map<int,int>::iterator it = mlf_map.begin(); it != mlf_map.end(); ++it) 
	{
		result+=1;
	}

	std::cout<<result;
	return 0;
}