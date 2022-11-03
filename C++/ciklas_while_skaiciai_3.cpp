#include <iostream>
using namespace std;

int main()
{
    int a,sk,skaitmenys=0;
    cin>>a;
    while(a>0)
    {
        sk=a%10;
        a=a/10;
        skaitmenys++;
    }
    cout<<skaitmenys;

    return 0;
}
