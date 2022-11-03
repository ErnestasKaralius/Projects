#include <fstream>
using namespace std;

struct rezultatas {
    int diena;
    int laikas;
};

void skaitymas(int&d, rezultatas R[]);
int begimo_trukme(int pval, int pmin, int gval, int gmin);
int trumpiausias_begimas(int d, rezultatas R[]);
void rasymas(int d, rezultatas R[]);

int main()
{
    int d;
    rezultatas R[31];

    skaitymas(d,R);
    rasymas(d,R);

    return 0;
}

void skaitymas(int&d, rezultatas R[])
{
    int pval, pmin; // Pradžios valanda ir minutė
    int gval, gmin; // Pabaigos valanda ir minutė
    int rytas, vakaras;
    ifstream fd("begimas_data.txt");

    fd>>d;
    for(int i=0; i<d; i++)
    {
        fd>>R[i].diena;

        // Bėgimo laikas ryte
        fd>>pval>>pmin;
        fd>>gval>>gmin;

        rytas = begimo_trukme(pval,pmin,gval,gmin);

        // Bėgimo laikas vakare
        fd>>pval>>pmin;
        fd>>gval>>gmin;

        vakaras = begimo_trukme(pval,pmin,gval,gmin);

        R[i].laikas = rytas + vakaras;

        // Jei bent vieną kartą praleistas bėgimas, diena bus perrašyta kita
        if(rytas == 0 || vakaras == 0)
        {
            d--;
            i--;
        }
    }

    fd.close();
}

int begimo_trukme(int pval, int pmin, int gval, int gmin)
{
    int trukme;
    trukme = gval*60 + gmin - (pval*60 + pmin); // Valandos paverčiamos į minutes

    return trukme;
}

int trumpiausias_begimas(int d, rezultatas R[])
{
    int maz = 0;
    for(int i=1; i<d; i++)
        if(R[i].laikas < R[maz].laikas)
            maz = i;

    return maz;
}

void rasymas(int d, rezultatas R[])
{
    int maz = trumpiausias_begimas(d,R);
    ofstream fr("begimas_rez.txt");

    fr<<"Minimalus laikas\n";
    fr<<R[maz].laikas;

    fr<<"\nDienos\n";
    for(int i=0; i<d; i++)
        if(R[i].laikas == R[maz].laikas)
            fr<<R[i].diena<<" ";

    fr.close();
}
