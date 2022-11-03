#include <iostream>
using namespace std;

int main()
{
    int a,sk,lyg=0,nelyg=0;
    cin>>a;
    while(a>0)
    {
        sk=a%10;
        a=a/10;
        if(sk%2==0)lyg++;
            else nelyg++;
    }
    cout<<"Lyginiu skaiciu: "<<lyg<<endl;
    cout<<"Nelyginiu skaiciu: "<<nelyg;

    return 0;
}
