#include <iostream>
using namespace std;

int main()
{
    int t1,k,n=0,t,t2;
    cin>>t1>>k>>t;

    while(t1<t)
    {
        n++;
        t=t-t1;
        t1=t1+k;
    }
    cout<<n;

    return 0;
}
