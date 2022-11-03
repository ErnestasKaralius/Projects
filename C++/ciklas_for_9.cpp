#include <iostream>
using namespace std;

int main()
{
    int sk,kiekis=0;
    for(sk=1000; sk<10000; sk++)
        if(sk/1000 + sk/100%10 == sk%100/10 + sk%10)
        {
            cout<<sk<<endl;
            kiekis++;
        }
    cout<<"Ju yra: "<<kiekis;

    return 0;
}
