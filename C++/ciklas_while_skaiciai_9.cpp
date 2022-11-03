#include <iostream>
using namespace std;

int main()
{
    int a,b,sk=2,taskai=0;
    cin>>a>>b;
    while(sk<=a)
    {
        if(a%sk==0&&b%sk==0)taskai++;
        sk++;
    }

    if(taskai==0)cout<<"Skaiciai yra tarpusavyje pirminiai";
        else cout<<"Skaiciai nera tarpusavyje pirminiai";

    return 0;
}
