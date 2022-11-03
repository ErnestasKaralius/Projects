#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int md,d=0,m=0;
    double mvid;
    cin>>md;
    while(md!=0)
    {
        d++;
        m=m+md;
        cin>>md;
    }
    mvid=(double)m/d;
    cout<<d<<endl;
    cout<<m<<endl;
    cout<<fixed<<setprecision(0)<<mvid;

    return 0;
}
