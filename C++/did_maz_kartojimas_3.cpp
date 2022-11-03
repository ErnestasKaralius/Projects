#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int n,i;
    double t,m,v,did,maz,vt;
    cin>>n>>m>>v;
    t=m/v;
    did=t; maz=t;
    vt=t;

    for(i=1;i<n;i++)
    {
        cin>>m>>v;
        t=m/v;
        if(t>did) did=t;
        if(t<maz) maz=t;
        vt=vt+t;
    }
    cout<<fixed<<setprecision(3)<<"Didziausias tankis: "<<did<<endl;
    cout<<fixed<<setprecision(3)<<"Maziausias tankis: "<<maz<<endl;
    cout<<fixed<<setprecision(3)<<vt/i;


    return 0;
}
