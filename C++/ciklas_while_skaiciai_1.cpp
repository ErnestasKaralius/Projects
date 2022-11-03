#include <iostream>
using namespace std;

int main()
{
    int a,s=0,sk;
    cin>>a;
    while(a>0)
    {
        sk=a%10;
        a=a/10;
        s=s+sk;
    }
    cout<<s;

    return 0;
}
