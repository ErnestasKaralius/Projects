#include <iostream>
using namespace std;

int main()
{
    int m=0,k=0,me;
    cin>>me;
    while(me!=0)
    {
        m=m+me;
        if(me>100) k++;
        cin>>me;
    }
    cout<<"Bendra zuvu mase: "<<m<<endl;
    cout<<"Zuvu, sunkesniu kaip 100 gramu kiekis: "<<k;

    return 0;
}
