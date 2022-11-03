#include <iostream>
using namespace std;

int main()
{
    double p,s,d;
    int t,i=1;
    cin>>s>>p>>t;
    while(i<=t)
    {
        d=s*(1+p/100);
        s=d;
        i++;
    }
    cout<<"Indelis: "<<d;

    return 0;
}
