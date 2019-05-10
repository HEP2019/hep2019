#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

int main()
{
    int n_edges, n_ribs;
    int start, destination;

    std::cin>>n_edges>>n_ribs>>start>>destination;

    std::vector< std::vector<int> > edges (n_edges+1);

    for(int i=0; i<n_ribs; ++i){
        int a,b;
        std::cin>>a;
        std::cin>>b;
        // std::cout<<a<<b<<"\n";
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    std::vector<int> dist(n_edges+1);
    std::vector<bool> used(n_edges+1, false);

    used[start] = true;
    dist[start] = 0;

    std::queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (int i = 0; i < (int) edges[current].size(); i++) {
          int v = edges[current][i];
          if (!used[v]) {
            // std::cout<<v<<"\n";
            used[v] = true;
            dist[v] = dist[current] + 1;
            q.push(v);
            if(v==destination) goto finish;
          }
        }
    }

    finish:
    // for(int n : dist){ std::cout<<n<<"\n"; }
        std::cout<<dist[destination]-1;

    return 0;
}