#include <iostream>
#include <vector>

using namespace std;

void quicksort(int long *mas, unsigned int long first, unsigned int long last)
{
    int long mid, count;
    int long f=first, l=last;
    mid=mas[(f+l) / 2];
    do
    {
        while (mas[f]<mid) f++;
        while (mas[l]>mid) l--;
        if (f<=l)
        {
            count=mas[f];
            mas[f]=mas[l];
            mas[l]=count;
            f++;
            l--;
        }
    } while (f<l);
    if (first<l) quicksort(mas, first, l);
    if (f<last) quicksort(mas, f, last);
}
int main()
{
    unsigned int long N,K,B,C,M,A1,Ai1,Ai,X;
    cin>>N>>K>>B>>C>>M>>A1;
    int long *mn = new int long[N];
    mn[0]=A1;
    
    for(int long i=1;i<N; i++){
        mn[i]=(mn[i-1]*B+C)%M;
    }
    
    quicksort(mn,0,N-1);
    
    for(int i=N-K;i <N;i++){
        cout << mn[i]<<" ";
    }
    return 0;
}
