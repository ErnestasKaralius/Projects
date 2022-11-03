#include <iostream>
using namespace std;

int main()
{
    int a,b,sk1,sk2,sk3,sk4;
    cin>>a>>b;
    for(a; a<=b; a++)
    {
        sk1=a;
        sk2=sk1+1;
        if(sk2>9) sk2=sk2%10;
        sk3=sk2+1;
        if(sk3>9) sk3=sk3%10;
        sk4=sk3+1;
        if(sk4>9) sk4=sk4%10;

        cout<<sk1*1000+sk2*100+sk3*10+sk4<<endl;
    }
    return 0;
}
