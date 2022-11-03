#include <iostream>
using namespace std;

int main()
{
    int x,k=0,s=0;
    cin>>x;
    while(x!=0)
    {
        if(x%10<=5)s=s+x;
        k++;
        cin>>x;
    }
    cout<<k<<endl;
    cout<<s;

    return 0;
}
