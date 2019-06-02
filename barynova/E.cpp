#include "iostream"
#include <stdlib.h>

using namespace std;

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}
int main() {
  int BracNum, SerNum, count = 0;
  int Brak[1000000], Ser[1000000];

  cin >> BracNum;

  for (int i = 0; i < BracNum; i++){
    cin >> Brak[i];
  }
  cin >> SerNum;
  for(int i = 0; i < SerNum; i++){
    cin >> Ser[i];
  }
  qsort (Ser, SerNum, sizeof(int), compare);

  int i = 0;
  int j = 0;

  while ((i < BracNum)*(j < SerNum)){

    if (Brak[i] == Ser[j]){
      count ++;
      j++;
    }
    else if (Brak[i] < Ser[j]) i++;
    else if (Brak[i] > Ser[j]) j++;
  }

  cout << count << endl;
  return 0;
}
