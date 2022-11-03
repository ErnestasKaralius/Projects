#include <iostream>
using namespace std;

int main()
{
    int kaina,uzsak=0,d=0;
    double vidurkis=0;
    cin>>kaina;
    while(kaina!=0)
    {
        d++;
        if(kaina>100) uzsak++;
        vidurkis=vidurkis+kaina;
        cin>>kaina;
    }
    cout<<uzsak<<endl;
    cout<<(double)vidurkis/d<<endl;
    cout<<d;

    return 0;
}
