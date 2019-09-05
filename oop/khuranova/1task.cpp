// problem_I.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vector>
#include <stdio.h>
#include <queue>
#include <iostream>
#include <fstream>
 
using namespace std;

int main ()
{
	ifstream fin("input.txt");
        vector < vector<int> > g; // граф
        int n; // число вершин
        int s; // стартовая вершина (вершины везде нумеруются с нуля)
		int zviazki;
		int finish; 
		cin >> n;//fin >> n;
		cin >> zviazki;//fin >> zviazki;
		cin >> s; //fin >> s;
				s=s-1;
		cin >> finish;//fin >> finish;
				finish=finish-1;
         // чтение графа
        int Adj[100][100];

		for(int i = 0; i<n; i++)
		for(int j = 0; j<n; j++)
			Adj[i][j]=0;
		
		for(int i = 0; i<zviazki; i++)
		{
			int AA, BB;
		cin >> AA>>BB;//fin >> AA>>BB;
			Adj[AA-1][BB-1]=1;
			Adj[BB-1][AA-1]=1;
		}

		
        for (int i = 0; i<n; i++)
        {
                g.push_back(vector<int>());
                for(int j = 0; j<n; j++)
                {
                    if(Adj[i][j])
                        g[i].push_back(j);
                        /*g[i].push_back(0);
                        g[i][j]=Adj[i][j];*/
                }
        }
        queue<int> q;
        q.push (s);
        vector<bool> used (n);
        vector<int> d (n), p (n);
        used[s] = true;
        p[s] = -1;
        while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (size_t i=0; i<g[v].size(); ++i) 
                {
                        int to = g[v][i];
                        if (!used[to]) 
                        {
                                used[to] = true;
                                q.push (to);
                                d[to] = d[v] + 1;
                                p[to] = v;
                        }
                }
        }
			
                cout << d[finish]-1;
        
        cout << endl;
        system("pause");
        return 0;
}

