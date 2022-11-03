#include <iostream>
using namespace std;

int main()
{
    int m,n,k=0;
    cin>>m>>n;
    for(m;m<=n;m++) if(m%10==m/100) {cout<<m<<endl;k++;}
    cout<<"Ju yra: "<<k;

    return 0;
}
