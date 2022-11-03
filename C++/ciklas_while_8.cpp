#include<iostream>
using namespace std;

int main()
{
    int t,n,d=0;
    cin>>t>>n;
    while(t>0)
    {
        d++;
        if(d%2==0) t=t-n;
            else t=t-n*2;
    }
    cout<<"Keliaus dienu: "<<d;

    return 0;
}
