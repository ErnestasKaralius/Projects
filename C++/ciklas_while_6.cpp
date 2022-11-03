#include <iostream>
using namespace std;

int main()
{
    int m1,m,d=0,n;
    cin>>m1>>m>>n;
    while(n>0)
    {
        d++;
        n=n-m1;
        m1=m1+m;
    }
    cout<<d;

    return 0;
}
