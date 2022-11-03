#include <iostream>
using namespace std;

int main()
{
    int n,t,maz=0,i,eile=0;
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>t;
        if(t>0&&maz==0){maz=t; eile=i;}
        if(t<maz&&t>0) {maz=t; eile=i;}
    }
    cout<<maz<<" "<<eile;

    return 0;
}
