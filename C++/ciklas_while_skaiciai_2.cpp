#include <iostream>
using namespace std;

int main()
{
    int a,sand=1,sk;
    cin>>a;
    while(a>0)
    {
        sk=a%10;
        a=a/10;
        sand=sand*sk;
    }
    cout<<sand;


    return 0;
}
