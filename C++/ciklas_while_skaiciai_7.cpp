#include <iostream>
using namespace std;

int main()
{
    int n,sk=1,sum=0;
    cin>>n;
    while(sum<n)
    {
        sum=sum+sk;
        sk++;
    }
    if(sum==n)cout<<"Taip";
        else cout<<"Ne";

    return 0;
}
