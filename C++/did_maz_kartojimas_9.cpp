#include <iostream>
using namespace std;

int main()
{
    int n,i,sdg=1;
    cin>>n;
    for(i=1;i<=n;i++)sdg=sdg*i;
    if(n<0)cout<<"Faktorialas is neigiamo skaiciaus negalimas";
        else cout<<sdg;

    return 0;
}
