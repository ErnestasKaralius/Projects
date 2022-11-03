#include <iostream>
using namespace std;

int main()
{
    int a,sk;
    cin>>a;
    while(a>0)
    {
        sk=a%10;
        a=a/10;
    }
    cout<<sk;
    return 0;
}
