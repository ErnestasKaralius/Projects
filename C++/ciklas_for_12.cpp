#include <iostream>
using namespace std;

int main()
{
    int n,sk,suma=0;
    cin>>n;
    for(sk=2; sk<n; sk++)
        if(n%sk==0){suma++; break;}

    if(suma>=1) cout<<"Skaicius sudetinis";
        else cout<<"Skaicius pirminis";

    return 0;
}
