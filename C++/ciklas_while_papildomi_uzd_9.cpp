#include <iostream>
using namespace std;

int main()
{
    int t,s1,s2,t1=0,t2=0;
    cin>>t;
    while(t>t1 || t>t2)
    {
        cin>>s1>>s2;
        t1=t1+s1;
        t2=t2+s2;
    }
    if(t1>t2)cout<<"Laimejo 1 draugas";
        else if(t2>t1)cout<<"Laimejo 2 draugas";
            else if(t2==t1) cout<<"Lygiosios";

    return 0;
}
