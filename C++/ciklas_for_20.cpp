#include <iostream>
using namespace std;

int main()
{
    int m,n;
    cin>>m>>n;
    for(m; m<=n; m++)
    {
        if(m%100!=0 && m%4==0) cout<<m<<" ";
            else if(m%400==0) cout<<m<<" ";
    }
    return 0;
}
