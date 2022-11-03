#include <iostream>
using namespace std;

int main()
{
    int m,k,mm,d=0,s;
    cin>>m>>k>>mm>>s;
    while(s>0)
    {
        s=s-mm*m;
        m=m+k;
        d++;
        cout<<s<<endl;
    }
    cout<<d;

    return 0;
}
