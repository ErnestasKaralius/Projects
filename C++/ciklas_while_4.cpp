#include <iostream>
using namespace std;

int main()
{
    int y,x,m,n,k,i=1;
    cin>>m>>n>>k;
    x=m;
    while(i<=k)
    {
        i++;
        y=5*x+3;
        cout<<x<<" "<<y<<endl;
        x=x+n;
    }

    return 0;
}
