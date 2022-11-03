#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    int a,b;
    double y;
    cin>>a>>b;
    for(a; a<=b; a++)
    {
        y=sqrt(a+5)/(7*a-9)+5;
        if(y!=y || sqrt(a+5)<0 || 7*a-9==0) cout<<"xxx"<<endl;
            else cout<<fixed<<setprecision(2)<<y<<endl;
    }
    return 0;
}
