#include <iostream>
using namespace std;

int main()
{
    int s,n,h,k;
    cin>>s>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>h>>k;
        s=s-h*2+k;
    }
    cout<<s;

    return 0;
}
