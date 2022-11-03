#include <fstream>
using namespace std;

struct traukinys {
    string nr;
    string marsrutas;
    int h;
    int m;
    int mn; // Stovėjimo trukmė
};

void skaitymas(int&n, traukinys T[], int&h0, int&m0);
void salinimas(int&n, traukinys T[], int h0, int m0);
void rikiavimas(int n, traukinys T[]);
void skaitymas(int n, traukinys T[]);

int main()
{
    int n;
    traukinys T[100];
    int h0, m0;


    skaitymas(n,T,h0,m0);
    salinimas(n,T,h0,m0);
    rikiavimas(n,T);
    skaitymas(n,T);

    return 0;
}

void skaitymas(int&n, traukinys T[], int&h0, int&m0)
{
    ifstream fd("traukiniu_tvarkarastis_data.txt");
    fd>>n;
    for(int i=0; i<n; i++)
    {
        fd>>T[i].nr;
        fd>>T[i].marsrutas;
        fd>>T[i].h>>T[i].m;
        fd>>T[i].mn;
    }
    fd>>h0>>m0;

    fd.close();
}

void salinimas(int&n, traukinys T[], int h0, int m0)
{
    // Šalinami traukiniai, kurių atvykimo laikas viršija h0 ir m0
    for(int i=0; i<n; i++)
        if(T[i].h*60 + T[i].m >= h0*60 + m0)
        {
            T[i]=T[n-1];
            n--;
            i--;
        }

    // Šalinami traukiniai, kurių išvykimo laikas mažesnis už h0 ir m0
    for(int i=0; i<n; i++)
    {
        T[i].h += (T[i].m + T[i].mn)/60;
        T[i].m = (T[i].m + T[i].mn)%60;

        if(T[i].h*60 + T[i].m <= h0*60 + m0)
        {
            T[i]=T[n-1];
            n--;
            i--;
        }
    }
}

void rikiavimas(int n, traukinys T[])
{
    for(int i=0; i<n-1; i++)
        for(int j=i+1; j<n; j++)
            if(T[i].h*60 + T[i].m < T[j].h*60 + T[j].m)
                swap(T[i],T[j]);
}

void skaitymas(int n, traukinys T[])
{
    ofstream fr("traukiniu_tvarkarastis_rez.txt");

    for(int i=0; i<n; i++)
        fr<<T[i].nr<<" "<<T[i].marsrutas<<" "<<T[i].h<<" "<<T[i].m<<endl;

    fr.close();
}


