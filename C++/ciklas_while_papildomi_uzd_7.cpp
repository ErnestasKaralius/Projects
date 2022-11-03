#include <iostream>
using namespace std;

int main()
{
    int n,k=0;
    cin>>n;
    while(n>0)
    {
        k++;
        n=n-2*k;
        if(n<0)k--;
    }
    cout<<k;

    return 0;
}
