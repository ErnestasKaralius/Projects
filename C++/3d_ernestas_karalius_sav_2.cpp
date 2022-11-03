#include <iostream>
using namespace std;

int main()
{
    int a,b,x,y;
    cin>>a>>b;
    for(x=a; x<=b; x++)
    {
        y=7*(x*x)-9*x+3;
        cout<<y<<endl;
    }

    return 0;
}
