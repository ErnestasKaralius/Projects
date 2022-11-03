#include <iostream>
using namespace std;

int main()
{
    int a,b,c,d=1;
    cin>>a>>b>>c;
    while(a<=c)
    {
        a=a+b;
        d++;
    }
    cout<<d;

    return 0;
}
