#include <iostream>
using namespace std;

int main()
{
    int n,taskai=0,sk=2;
    cin>>n;
    while(sk<n)
    {
        if(n%sk==0)taskai++;
        sk++;
    }
    if(taskai>=1)cout<<"Skaicius sudetinis";
        else cout<<"Skaicius pirminis";

    return 0;
}
