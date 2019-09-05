#include<cstdio>
#include<queue>
#include<cstring>
#include<vector>
#include<iostream>

std::vector< std::vector <int> > graph; 
std::vector< std::vector <int> > flowPassed;
std::vector< std::vector <int> > g;

std::vector< int > pars;
std::vector< int > path_now;

int search(int, int);
int CountByKarps(int, int);

int main()
{
   int nod_num, edge_num;  
   int begin, end; 
   std::cin>>nod_num>>edge_num>>begin>>end;

   //SETING UP GLOBAL VARS
   graph.resize(nod_num+1, std::vector < int > (nod_num+1,0));
   flowPassed.resize(nod_num+1, std::vector < int > (nod_num+1,0));
   g.resize(nod_num+1);

   pars.resize(edge_num+1,-1);
   path_now.resize(edge_num+1,0);

   for(int ed = 0; ed < edge_num; ed++)
   { 
      int from, to, weight;
      std::cin>>from>>to>>weight;
      
      graph[from][to] = weight; graph[to][from] = weight;
      g[from].push_back(to); g[to].push_back(from);
   }

   std::cout<<CountByKarps(begin, end)<<"\n";
   return 0;
}

int search(int start_n, int end_n)//breadth search
{
   std::fill (pars.begin(),pars.end(),-1);
   std::fill (path_now.begin(),path_now.end(),0);
   
   std::queue<int> q;
   q.push(start_n);
   pars[start_n] = -1;
   path_now[start_n] = 999;
   while(!q.empty())
   {
      int current = q.front();
      q.pop();
      for(int i=0; i<g[current].size(); ++i)
      {
         int to = g[current][i];
         if(pars[to] == -1)
         {
            if(graph[current][to] - flowPassed[current][to] > 0)
            {
               pars[to] = current;
               path_now[to] = std::min(path_now[current],
               graph[current][to] - flowPassed[current][to]);
               if(to == end_n)
               {
                  return path_now[end_n];
               }
               q.push(to);
            }
         }
      }
   }
   return 0;
}
int CountByKarps(int begin, int end)
{
   int maxFlow = 0;
   while(true)
   {
      int flow = search(begin, end);
      if (flow == 0)
      {
         break;
      }
      maxFlow += flow;
      int currNode = end;
      while(currNode != begin)
      {
         int prevNode = pars[currNode];
         flowPassed[prevNode][currNode] += flow;
         flowPassed[currNode][prevNode] -= flow;
         currNode = prevNode;
      }
   }
return maxFlow;
}
