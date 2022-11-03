#include <iostream>
using namespace std;

int main()
{
    int t,n,i,sk;
    cin>>t>>n;
    for(i=1; i<=n; i++)
    {
        cin>>sk;
        t=t+sk;
    }
    cout<<t;

    return 0;
}
