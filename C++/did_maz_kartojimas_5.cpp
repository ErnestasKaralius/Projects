#include <iostream>
using namespace std;

int main()
{
    int n,saskes=1,i=2;
    cin>>n;
    while(saskes<=n)
    {
        n=n-saskes;
        saskes++;
    }
    cout<<"Eiles: "<<saskes/8<<endl;
    cout<<"Liko: "<<n;

    return 0;
}

