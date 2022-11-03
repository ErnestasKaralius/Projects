#include <iostream>
using namespace std;

int main()
{
    int m,d=0,a=1;
    cin>>m;
    while(m>0)
    {
        d++;
        m=m-a;
        a=a+1;
    }
    cout<<d;

    return 0;
}
