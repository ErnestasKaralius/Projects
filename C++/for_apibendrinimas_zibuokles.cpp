#include <iostream>
using namespace std;

int main()
{
    int n,z,d,sum=0;
    cin>>n;
    for(d=1;d<=n && sum<20; d++)
    {
        cin>>z;
        sum=sum+z;
        if(sum>=20) {cout<<"Prazydejo per "<<d;}
            else if(d==n && sum<20) cout<<"Neprazydejo";
    }
    return 0;
}
