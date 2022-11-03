#include <iostream>
using namespace std;

int main()
{
    int m,n,sk1,sk2,sum=0;
    cin>>m>>n;
    for(m; m<=n; m++)
    {
        sk1=m/1000;
        sk2=m%1000;

        if(sk1==sk2) sum++;
    }
    cout<<sum;

    return 0;
}
