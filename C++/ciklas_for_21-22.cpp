#include <iostream>
using namespace std;

int main()
{
    int n,i,sk,did,maz,dvieta=1,mvieta=1;
    cin>>n>>sk;
    did=sk; maz=sk;
    for(i=2; i<=n; i++)
    {
        cin>>sk;
        if(sk>did) {did=sk; dvieta=i;}
            else if(sk<maz) {maz=sk; mvieta=i;}

    }
    cout<<"Didziausias skaicius: "<<did<<". Vieta sekoje: "<<dvieta<<endl;
    cout<<"Maziausias skaicius: "<<maz<<". Vieta sekoje: "<<mvieta;

    return 0;
}
