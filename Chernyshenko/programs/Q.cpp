#include <iostream>
using namespace std;

int main(){
	long int C=1, D=1000000007, N;
	long long hash=0;
	string text;
	cin>> text;
for(int N = 0; N < text.length(); N++){
	hash=(hash+int(text[N])*C)%D;
	C=(C*1009)%D;
}
cout<<hash<<endl;
}