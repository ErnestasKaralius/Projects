#include <fstream>
#include <iostream>
using namespace std;

struct zirnis {
    char kokybe;
    int dydis;
};

void skaitymas(int&sk, zirnis Z[]);
void salinimas(int&sk, zirnis Z[]);
void rikiavimas(int sk, zirnis Z[]);

int skirtingu_zirniu_skaicius(int sk, zirnis Z[]);
void rasymas(int sk, zirnis Z[]);

int main()
{
    int sk;
    zirnis Z[500];

    skaitymas(sk,Z);
    salinimas(sk,Z);
    rikiavimas(sk,Z);
    rasymas(sk,Z);

    return 0;
}

void skaitymas(int&sk, zirnis Z[])
{
    ifstream fd("pelenes_data.txt");

    fd>>sk;
    for(int i=0; i<sk; i++)
        fd>>Z[i].kokybe>>Z[i].dydis;

    fd.close();
}

void salinimas(int&sk, zirnis Z[])
{
    for(int i=0; i<sk; i++)
        if(Z[i].kokybe == 'b')
        {
            Z[i]=Z[sk-1];
            sk--;
            i--;
        }
}

void rikiavimas(int sk, zirnis Z[])
{
    for(int i=0; i<sk-1; i++)
        for(int j=i+1; j<sk; j++)
            if(Z[i].dydis > Z[j].dydis)
                swap(Z[i],Z[j]);
}

int skirtingu_zirniu_skaicius(int sk, zirnis Z[])
{
    int kiekis=1;
    for(int i=1; i<sk; i++)
        if(Z[i].dydis != Z[i-1].dydis)
            kiekis++;

    return kiekis;
}

void rasymas(int sk, zirnis Z[])
{
    ofstream fr("pelenes_rez.txt");

    for(int i=0; i<sk; i++)
        fr<<Z[i].dydis<<" ";

    fr<<"\n"<<skirtingu_zirniu_skaicius(sk,Z);

    fr.close();
}
