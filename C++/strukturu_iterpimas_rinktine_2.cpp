#include <fstream>
#include <iostream>
using namespace std;

struct zaidejas {
    char Vardas[26];
    double naudingumas;
};

void skaitymas(int&np, int&na, zaidejas P[], zaidejas N[]);
void naujoku_iterpimas(int&np, int na, zaidejas P[], zaidejas N[]);
int vietos_radimas(int np, zaidejas P[], zaidejas N);
void rasymas(int np, zaidejas P[]);

int main()
{
    int np,na;
    zaidejas P[100],N[100];

    skaitymas(np,na,P,N);
    naujoku_iterpimas(np,na,P,N);
    rasymas(np,P);

    return 0;
}

void skaitymas(int&np, int&na, zaidejas P[], zaidejas N[])
{
    ifstream fd("nacionaline_rinktine_2_data.txt");

    fd>>np;
    fd.ignore();
    for(int i=0; i<np; i++)
    {
        fd.get(P[i].Vardas, 25);
        fd>>P[i].naudingumas;
        fd.ignore();
    }

    fd>>na;
    fd.ignore();
    for(int i=0; i<na; i++)
    {
        fd.get(N[i].Vardas, 25);
        fd>>N[i].naudingumas;
        fd.ignore();
    }

    fd.close();
}

int vietos_radimas(int np, zaidejas P[], zaidejas N)
{
    for(int i=0; i<np; i++)
        if(N.naudingumas <= P[np-1].naudingumas)
            return np;

        else if(N.naudingumas > P[0].naudingumas)
            return 0;

        else if(P[i].naudingumas >= N.naudingumas && P[i+1].naudingumas < N.naudingumas)
            return i+1;
}

void naujoku_iterpimas(int&np, int na, zaidejas P[], zaidejas N[])
{
    int vieta;
    for(int i=0; i<na; i++)
    {
        vieta = vietos_radimas(np,P,N[i]);
        for(int j=np; j>vieta; j--)
            P[j]=P[j-1];

        P[vieta]=N[i];
        np++;
    }
}

void rasymas(int np, zaidejas P[])
{
    ofstream fr("nacionaline_rinktine_2_rez.txt");

    for(int i=0; i<np; i++)
        fr<<P[i].Vardas<<" "<<P[i].naudingumas<<endl;

    fr.close();
}
