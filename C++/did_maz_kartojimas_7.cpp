#include <iostream>
using namespace std;

int main()
{
    int n,h,i,ugis,kiekis=0;
    cin>>n>>h;
    for(i=1;i<=n;i++)
    {
        cin>>ugis;
        if(ugis>h) kiekis++;
    }
    cout<<kiekis;

    return 0;
}
