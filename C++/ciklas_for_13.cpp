#include <iostream>
using namespace std;

int main()
{
    int sk,i,suma=0,nsand=1,tsuma=0;
    for(i=1;i<=5; i++)
    {
        cin>>sk;
        suma=suma+sk;
        if(sk<0) nsand=nsand*sk;
            else tsuma=tsuma+sk;
    }
    cout<<"Kvadratas: "<<suma*suma<<endl;
    cout<<"Aritmetinis vidurkis: "<<(double)suma/5<<endl;
    cout<<"Neigiamu skaiciu sandauga: "<<nsand<<endl;
    cout<<"Teigiamu skaiciu suma: "<<tsuma;

    return 0;
}
