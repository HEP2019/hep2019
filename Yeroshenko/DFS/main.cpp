#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int n;
vector < vector<int> > g;
vector<char> used;

void dfs (int v) {
	used[v] = true;
	cout << v + 1 << endl;

	for (int i = 0; i < n; ++i){
		if (!used[i] && g[v][i] == 1)
			dfs (i);
	}
}


int main(int argc, char const *argv[])
{
	fstream fin("vertex.txt", ios_base::in);
	int a, b;

	int stop; 

	fin >> n;

	g = vector < vector<int> >(n, vector<int>(n,0));
	used = vector<char>(n, false);

	while (fin >> a >> b) {
		g[a-1][b-1] = 1;
		g[b-1][a-1] = 1;
	}
	fin.close();

	for (int i  = 0; i < n; ++i){
		for (int j = 0; j < n; ++j)
			cout << g[i][j] << " ";
		cout << "\n";
	}

	dfs(0);
	
	return 0;
}