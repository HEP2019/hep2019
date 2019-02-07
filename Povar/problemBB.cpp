#include <iostream>
 
using namespace std;
 
int main()
{
   int long N,Q = 0;
   cout << "Please enter a number"<<endl;
   cin >> N;
   if(N==0)
    {
        cout<< "10"<<endl;
        return 0;
    }
   if(N<=9)
    {
        cout << N << endl;
        return 0;
    }
   else
    {
       int gcd = 9, pos = 1; 

       while(gcd > 1)
        {
           while((N%gcd) == 0)
           {
               Q = Q + pos*gcd;
               pos = pos*10;
               N = N/gcd;
           }
           gcd--; 
        }
        if(N>1)
            {                                               
                cout <<"-1"<< endl;
                return 0;  
            }
        cout << Q << endl;
        return 0;
    }    
}
