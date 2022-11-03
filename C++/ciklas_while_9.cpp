#include <iostream>
using namespace std;

int main()
{
    int n,x,d=0,liko;
    cin>>n;
    while(n>0)
    {
        cin>>x;
        n=n-x;
        if(n>=0) d++;
    }
    cout<<"Saldainiu uzteks: "<<d<<endl;
    if(n<0)
    {
        liko=n+x;
        cout<<"Liko saldainiu: "<<liko;
    }

    return 0;
}
