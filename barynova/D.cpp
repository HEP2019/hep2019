#include "iostream"
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int main(){

  int R;
  int N;


  cin >> R >> N;
  int x[5000];
  int y[5000];

  for (int  i = 0; i < N; i++){
    cin >> x[i] >> y[i];
  }

  int counter = 0;
  vector<double> angle;

  for (int i = 0; i < N ; i++){
    for (int j = 0; j < N; j ++){
      if (i != j) angle.push_back(atan2((y[i] - y[j]),(x[i] - x[j])));
    }
    sort(angle.begin(), angle.end());
    int cntr = 0;
    while(cntr < angle.size()-1){
        if (angle[cntr] == angle[cntr+1]){
        angle.erase(angle.begin()+cntr);
      }
      else cntr ++;
    }
    counter += angle.size();
    angle.clear();
  }

  cout << counter << endl;

  return 0;
}
