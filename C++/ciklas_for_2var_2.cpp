#include <iostream>
using namespace std;

int main()
{
    int x,t1,t2,a,b,c;
    cin>>t1>>t2;
    for(x=t1; x<=t2; x++)
    {
        a=x/100;
        b=x/10%10;
        c=x%10;
        if(a!=b && b!=c && a!=c) cout<<x<<endl;
    }
    return 0;
}
