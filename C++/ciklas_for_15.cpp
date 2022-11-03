#include<iostream>
using namespace std;

int main()
{
    int a1=1,a2=-2,an,n;
    cin>>n;
    for (int i=3; i<=n; i++)
    {
        an=a1+a2;
        a1=a2;
        a2=an;
    }
  cout<<an;

return 0;
}
