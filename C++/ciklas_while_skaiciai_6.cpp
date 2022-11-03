#include <iostream>
using namespace std;

int main()
{
    int a,b,ska,skb;
    cin>>a>>b;
    while(a>0) {ska=a%10; a=a/10;}
    while(b>0) {skb=b%10; b=b/10;}
    cout<<ska+skb;

    return 0;
}
