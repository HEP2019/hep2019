#include "iostream"
#include "string.h"

using namespace std;


int returnVal(char x)
{
    return (int)x;
}

int CalcCash (int Char[1000], int length ,int A, int M){
  long long int CalacultedCash = 0;


  for (int i = 0; i < length; i++){
    long long int cashe = Char[i];
    for (int j = 0; j < i; j++){

      cashe = cashe*A % M;
    }
    CalacultedCash += cashe;

    CalacultedCash = CalacultedCash % M;
  }
  return CalacultedCash;
}

int main(){

  string s;
  cin >> s;
  int C = 1009;
  int D = 1000000007;

  int Char[1000];
  int length = s.length();


  for (unsigned int i = 0; i < length; i++){
      Char[i] = returnVal(s[i]);
    }

  cout << CalcCash (Char, length, C, D) << endl;



 return 0;

}
