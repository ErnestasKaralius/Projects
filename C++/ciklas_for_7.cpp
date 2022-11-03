#include <iostream>
using namespace std;

int main()
{
    int sk,suma=0;
    for(sk=100; sk<1000; sk++)
        if(sk%10==4)
        {
            cout<<sk<<endl;
            suma++;
        }
    cout<<suma;

    return 0;
}

