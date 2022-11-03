#include <fstream>
using namespace std;

struct kategorija {
    string pavadinimas;
    int procentai;
};

struct portalas {
    string pavadinimas;
    int kiekis; // Kiek kategorijų
    kategorija K[30];
};

void skaitymas(int&n, portalas P[]);
void kategoriju_atrinkimas(int n, portalas P[], int&p, portalas N[]);
void salinimas(int j, int p, portalas N[]);
void rikiavimas(int p, portalas N[]);
void rasymas(int p, portalas N[]);


int main()
{
    int n,p;
    portalas P[30];
    portalas N[30]; // Atrinktas portalų sąrašas

    skaitymas(n,P);
    kategoriju_atrinkimas(n,P,p,N);
    rikiavimas(p,N);
    rasymas(p,N);

    return 0;
}

void skaitymas(int&n, portalas P[])
{
    ifstream fd("naujienos_data.txt");
    int sk;
    char zyme;

    fd>>n;
    for(int i=0; i<n; i++)
    {
        P[i].kiekis = 0;

        fd>>P[i].pavadinimas;
        fd>>P[i].K[0].pavadinimas;

        fd>>sk;
        int melagingi=0;
        for(int j=0; j<sk; j++)
        {
            fd>>zyme;
            if(zyme =='M') melagingi++;
        }
        P[i].K[0].procentai =(double)melagingi / sk * 100;
        P[i].kiekis++;
    }

    fd.close();
}


void kategoriju_atrinkimas(int n, portalas P[], int&p, portalas N[])
{
    p = 0;
    // Portalų su melagingomis kategorijomis atrinkimas
    for(int i=0; i<n; i++)
    {
        if(P[i].K[0].procentai >= 75)
        {
            N[p] = P[i];
            p++;
        }
    }
    // Portalų kategorijų sudėjimas
    for(int i=0; i<p-1; i++)
        for(int j=i+1; j<p; j++)
            if(N[i].pavadinimas == N[j].pavadinimas)
            {
                N[i].K[N[i].kiekis] = N[j].K[0];
                N[i].kiekis++;

                salinimas(j,p,N);
                p--;
                j--;
            }

}

void salinimas(int j, int p, portalas N[])
{
    for(int j; j<p-1; j++)
        swap(N[j],N[j+1]);
}


void rikiavimas(int p, portalas N[])
{
    for(int i=0; i<p-1; i++)
        for(int j=i+1; j<p; j++)
        {
            if(N[i].kiekis < N[j].kiekis)
                swap(N[i],N[j]);

            else if(N[i].kiekis == N[j].kiekis)
                if(N[i].pavadinimas > N[j].pavadinimas)
                    swap(N[i],N[j]);
        }
}

void rasymas(int p, portalas N[])
{
    ofstream fr("naujienos_rez.txt");

    if(p != 0)
        for(int i=0; i<p; i++)
        {
            fr<<N[i].pavadinimas<<" "<<N[i].kiekis<<"\n";
            for(int j=0; j<N[i].kiekis; j++)
                fr<<N[i].K[j].pavadinimas<<" "<<N[i].K[j].procentai<<"\n";
        }
    else fr<<"Neatitinka reikalavimo";

    fr.close();
}
