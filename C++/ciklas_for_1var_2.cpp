#include <iostream>
using namespace std;

int main()
{
    int x,a,c,tf1,tf2;
    cin>>tf1>>tf2;
    for(x=tf1; x<=tf2; x++)
    {
        a=x/100;
        c=x%10;
        if(a==c) cout<<x<<endl;
    }
    return 0;
}
