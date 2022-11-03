#include <iostream>
using namespace std;

int main()
{
    int n,k,i,s,v;
    cin>>n>>k;
    s=k;
    for(i=1;i<n;i++)
    {
        k=k+2;
        s=s+k;
    }
    cout<<s;

    return 0;
}
