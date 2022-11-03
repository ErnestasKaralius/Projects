#include <iostream>
using namespace std;

int main()
{
    int n,sk,i,did,maz,meile=1,deile=1;
    cin>>n>>sk;
    maz=sk;
    did=sk;
    for(i=2;i<=n;i++)
    {
        cin>>sk;
        if(sk>did){did=sk;deile=i;}
        if(sk<maz){maz=sk;meile=i;}
    }
    cout<<"Didziausias: "<<did<<" "<<deile<<endl;
    cout<<"Maziausias: "<<maz<<" "<<meile;

    return 0;
}
