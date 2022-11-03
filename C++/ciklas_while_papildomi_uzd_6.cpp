#include <iostream>
using namespace std;

int main()
{
    int s,kk,k=0,ks=0,p=0;
    cin>>s;
    while(s>0)
    {
        cin>>kk;
        s=s-kk;
        if(s>=0) {ks=ks+kk; k++;}
            else p=s+kk;
    }
    cout<<k<<endl;
    cout<<ks<<endl;
    cout<<p;

    return 0;
}
