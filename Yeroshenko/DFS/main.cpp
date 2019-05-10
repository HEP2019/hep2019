#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

int n;
vector < vector<int> > g;
vector<char> used;
stack<int> st;
vector< pair<int> > joints;

// void dfs (int v) {
// 	used[v] = true;
// 	cout << v + 1 << endl;

// 	for (int i = 0; i < n; ++i){
// 		if (!used[i] && g[v][i] == 1)
// 			dfs (i);
// 	}
// }

void dfs() {
	int i = 0;
	while (true) {
		cout << i + 1 << endl;
		used[i] = true;
		for (int j = n; j >=0 ; --j){
			if (g[i][j] == 1 && !used[j])
				st.push(j);
		}
		if (st.empty()) break;
		i = st.top();
		st.pop();
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
		joints.push_back(pair(a-1, b-1));
		g[a-1][b-1] = 1;
		g[b-1][a-1] = 1;
	}
	fin.close();

	for (int i  = 0; i < n; ++i){
		for (int j = 0; j < n; ++j)
			cout << g[i][j] << " ";
		cout << "\n";
	}

	dfs();
	
	return 0;
}