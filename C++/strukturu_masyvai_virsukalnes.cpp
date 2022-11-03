#include <fstream>
using namespace std;

struct virsukalne {
    string Pavadinimas;
    int aukstis;
};

void skaitymas(int&n, int&a, virsukalne V[]);
void salinimas(int&n, int a, virsukalne V[]);
void rikiavimas(int n, virsukalne V[]);
void rasymas(int n, virsukalne V[]);

int main()
{
    int n;
    virsukalne V[100];
    int a;

    skaitymas(n,a,V);
    salinimas(n,a,V);
    rikiavimas(n,V);
    rasymas(n,V);

    return 0;
}

void skaitymas(int&n, int&a, virsukalne V[])
{
    ifstream fd("virsukalnes_data.txt");

    fd>>n;
    for(int i=0; i<n; i++)
        fd>>V[i].Pavadinimas>>V[i].aukstis;

    fd>>a;

    fd.close();
}

void salinimas(int&n, int a, virsukalne V[])
{
    for(int i=0; i<n; i++)
        if(V[i].aukstis < a)
        {
            V[i]=V[n-1];
            n--;
            i--;
        }
}

void rikiavimas(int n, virsukalne V[])
{
    for(int i=0; i<n-1; i++)
        for(int j=i+1; j<n; j++)
            if(V[i].aukstis < V[j].aukstis)
                swap(V[i],V[j]);
}

void rasymas(int n, virsukalne V[])
{
    ofstream fr("virsukalnes_rez.txt");

    for(int i=0; i<n; i++)
        fr<<V[i].Pavadinimas<<endl;

    fr.close();
}

