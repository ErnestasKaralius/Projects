#include <iostream>
using namespace std;

int main()
{
    int n,i,j,sk,suma=0;
    cin>>n;
    for(i=1;i<=n;i++)
    {
        sk=1;
        for(j=1;j<=n;j++)sk=sk*i;
        suma=suma+sk;
    }
    cout<<suma;

    return 0;
}
