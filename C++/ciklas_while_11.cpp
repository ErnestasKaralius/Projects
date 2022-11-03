#include <iostream>
using namespace std;

int main()
{
    int balas,sk=0,pateko=0;
    cin>>balas;
    while(balas!=0)
    {
        sk++;
        if(balas>=5) pateko++;
        cin>>balas;
    }
    cout<<"Ejo mokiniu: "<<sk<<endl;
    cout<<"Pateko mokiniu: "<<pateko;

    return 0;
}
