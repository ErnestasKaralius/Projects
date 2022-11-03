#include <iostream>
using namespace std;

int main()
{
    int p,k,d=0,u;
    cin>>p>>k>>u;
    while(u>0)
    {
        u=u-p;
        p=p+k;
        d++;
        cout<<u<<endl;
    }
    cout<<d;

    return 0;
}
