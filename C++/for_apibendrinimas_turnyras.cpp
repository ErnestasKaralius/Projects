#include <iostream>
using namespace std;

int main()
{
    int n,i,sw,se,sd,lpr=0,lyg=0;
    cin>>n;
    for(i=1;i<=n; i++)
    {
        cin>>sw>>se>>sd;
        cout<<i<<"-asis surinko: "<<sw*1+se*0.5+sd*0<<endl;
        lpr=lpr+sw+sd;
        lyg=lyg+se;
    }
    cout<<"Laimeta/pralaimeta: "<<lpr<<endl;
    cout<<"Lygiosios: "<<lyg;

    return 0;
}
