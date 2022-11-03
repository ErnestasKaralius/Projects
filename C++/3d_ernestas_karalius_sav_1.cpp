#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int n,i,sk,sum=0,dalik=0;
    cin>>n;
    for(i=1; i<=n; i++)
    {
        cin>>sk;
        if(sk%2!=0) {sum=sum+sk; dalik++;}
    }
    cout<<fixed<<setprecision(2)<<(double)sum/dalik;

    return 0;
}
