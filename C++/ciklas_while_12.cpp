#include <iostream>
using namespace std;

int main()
{
    int veiksmas,sk,sum=0,skirtumas,ateminys=0,daugyba=1,did,maz;
    cin>>veiksmas; cin>>sk;
    skirtumas=sk;
    did=sk; maz=sk;
    while(sk!=0)
    {
        if(veiksmas==1) sum=sum+sk;
            else if(veiksmas==2) skirtumas=skirtumas-ateminys;
                else if (veiksmas==3) daugyba=daugyba*sk;
                    else if (veiksmas==4 && sk>did) did=sk;
                        else if (veiksmas==5 && sk<maz) maz=sk;
                        cin>>sk;
                        ateminys=sk;
    }
    if(veiksmas==1) cout<<sum;
        else if(veiksmas==2) cout<<skirtumas;
            else if(veiksmas==3) cout<<daugyba;
                else if(veiksmas==4) cout<<did;
                    else if(veiksmas==5) cout<<maz;

    return 0;
}
