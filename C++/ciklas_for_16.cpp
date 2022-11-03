#include <iostream>
using namespace std;

int main()
{
    int n,m,i,sk;
    cin>>n>>m;
    for(i=1; i<=m; i++)
    {
        cin>>sk;
        if(sk==1) n=n-2;
            else if(sk==2) n=n-5;
                else if(sk==3) n=n-3;

    }
    if(n<0) n=0;
    cout<<"Likutis: "<<n;

    return 0;
}
