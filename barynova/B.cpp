#include "iostream"
#include <vector>
#include <algorithm>

using namespace std;


int makeint (int n[6], int digs)
{
  int power = 1;
  int outnum = 0;

  for (int i = 0; i < digs; i++)
  {
    outnum += n[i]*power;
    power *= 10;
  }
  return outnum;
}


int main()
{

  int N;
  int K;

  cin >> N >> K ;
  int n[6];
  int digs = 0;

  while (N/10 != 0)
  {
    n[digs] = N % 10;
    digs ++;
    N /= 10;
  }
  n[digs] = N;
  digs ++;

  int swap;

  vector<int>  rearrange;
  rearrange.push_back(makeint(n, digs));
  int counter;

 if (K > digs) K = digs + (K - digs) % 2;

 for (int i = 0; i < K; i++){

  counter = rearrange.size();
  for (int i = 0; i < counter; i ++){
    for (int j = 0; j < digs ; j++){
      n[j] = rearrange[0]%10;
      rearrange[0] /= 10;
    }

    rearrange.erase(rearrange.begin());
    for (int j = 0; j < digs - 1; j++){
      for(int k = j + 1; k < digs; k++){
        swap = n[j];
        n[j] = n[k];
        n[k] = swap;
        rearrange.push_back(makeint(n, digs));
        swap = n[j];
        n[j] = n[k];
        n[k] = swap;

      }
    }
  }

  sort (rearrange.begin(), rearrange.end());

  int cntr = 0;
  while(cntr < rearrange.size()-1)
  {
    if (rearrange[cntr] == rearrange[cntr+1]){
      rearrange.erase(rearrange.begin()+cntr);
    }
    else cntr ++;
  }

}

  cout << rearrange[rearrange.size() - 1] << endl;
  return 0;
}
