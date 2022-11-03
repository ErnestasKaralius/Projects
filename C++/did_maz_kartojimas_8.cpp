#include <iostream>
using namespace std;

int main()
{
    int n,i=1,san,km,vieta;
    double k,mk;
    cin>>n>>san>>km;
    k=(double)san/km;
    mk=k;
    vieta=i;

    for(i=2;i<=n;i++)
    {
        cin>>san>>km;
        k=(double)san/km;
        if(k<mk){mk=k;vieta=i;}
    }
    cout<<"Maziausios sanaudos automobilio "<<vieta<<" - "<<mk;

    return 0;
}
