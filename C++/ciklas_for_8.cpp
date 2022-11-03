#include <iostream>
using namespace std;

int main()
{
    int sk,sk1,sk2,suma=0,kiekis=0;
    for(sk=10; sk<100; sk++)
    {
        sk1=sk/10;
        sk2=sk%10;
        if(sk1%2==0 && sk2%2==0)
        {
            cout<<sk<<endl;
            kiekis++;
            suma=suma+sk;
        }
    }
    cout<<"Ju yra: "<<kiekis<<endl;
    cout<<"Suma: "<<suma;
    return 0;
}
