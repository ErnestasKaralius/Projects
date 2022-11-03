#include <iostream>
using namespace std;

int main()
{
    int n, k=0;
    cin>>n;
    while(n>0)
    {
        if(n%2!=0) n=n-1;
            else if(n%2==0) n=n-(n/2);
            k++;
    }
    cout<<k;

    return 0;
}
