#include <iostream>
using namespace std;

int main()
{
    int tr1,tr2;
    cin>>tr1>>tr2;
    for(tr1; tr1<=tr2; tr1++)
        if(tr1%10+tr1/1000==tr1%100/10+tr1/100%10) cout<<tr1<<" ";

    return 0;
}
