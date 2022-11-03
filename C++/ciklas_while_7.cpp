#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int m,d=0,i=1;
    double s;
    cin>>m;
    s=m;
    while(m>0)
    {
        m=m-i;
        i++;
        d++;
    }
    cout<<"Perskaitys per: "<<d<<endl;
    cout<<fixed<<setprecision(2)<<"Vid: "<<(double)s/d;

    return 0;
}
