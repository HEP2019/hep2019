#include <iostream>
 
int main () {
  int base;
  std::cin >> base;
  
  long int num = 0;
  int cah = 0, cah1 = 1;
  bool key = true;

  while (key) 
    for (int i=9; i >= 2; --i) {
        if (base % i==0) {
            cah += i*cah1;
            num += cah;
            base /= i;
            cah = 0;
            cah1 *= 10;
            break;
        }
        if (i==2) {key = false;}
        }
        if (base<10){std::cout << num;}
        else {std::cout << -1;}
    
   return 0;    
}
