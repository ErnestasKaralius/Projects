#include<iostream>
using namespace std;

int main()
{
    int n,dal,kiekis=0,suma=0,sandauga=1;
    cin>>n;

    for(dal=1; dal<=n; dal++)
        if(n%dal==0)
        {
            cout<<dal<<endl;

            suma=suma+dal;
            sandauga=sandauga*dal;
            kiekis++;
        }
    cout<<"Kiekis: "<<kiekis<<" ";
    cout<<"Suma: "<<suma<<" ";
    cout<<"Sandauga: "<<sandauga;

    return 0;
}
