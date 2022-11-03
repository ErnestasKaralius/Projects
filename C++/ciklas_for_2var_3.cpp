#include <iostream>
using namespace std;

int main()
{
    int a,b,sk1,sk2,sk3,sk4;
    cin>>a>>b;
    for(a; a<=b; a++)
    {
        sk2=a;
        sk1=sk2+1;
        if(sk1>9) sk1=sk1%10;
        sk3=sk2-1;
        sk4=sk3+3;
        if(sk4>9) sk4=sk4%10;

        cout<<sk1*1000+sk2*100+sk3*10+sk4<<endl;
    }
    return 0;
}
