#include <iostream>
using namespace std;

int main()
{
    int a,sk=2;
    cin>>a;
    while(sk<=a) sk=sk*2;
    if(sk>a)sk=sk/2;
    cout<<sk;

    return 0;
}
