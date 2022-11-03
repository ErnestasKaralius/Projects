#include <fstream>
using namespace std;

struct diena {
    int laikas;
    int suvenyrai;
    int negamino;
};

void skaitymas(diena D[]);
int laikas_minutemis(int pv, int pm, int bv, int bm);
int pagamino_daugiausia(diena D[]);
void rasymas(diena D[]);

int main()
{
    diena D[32];

    skaitymas(D);
    rasymas(D);

    return 0;
}

void skaitymas(diena D[])
{
    ifstream fd("savanoryste_data.txt");

    int kiekis;
    int indeksas;
    int pv,pm, bv,bm; // Pradios ir baigimo laikas val ir min;

    // Nulinimas
    for(int i=1; i<=31; i++)
    {
        D[i].suvenyrai = 0;
        D[i].negamino = 0;
    }

    int d; // Diena
    fd>>d;
    for(int i=0; i<d; i++)
    {
        fd>>indeksas;
        fd>>pv>>pm>>bv>>bm;
        D[indeksas].laikas = laikas_minutemis(pv,pm,bv,bm);

        for(int j=0; j<5; j++)
        {
            fd>>kiekis;
            if(kiekis == 0) D[indeksas].negamino++;
                else D[indeksas].suvenyrai += kiekis;
        }
    }

    fd.close();
}

int laikas_minutemis(int pv, int pm, int bv, int bm)
{
    return 60*bv + bm - (60*pv + pm);
}

int pagamino_daugiausia(diena D[])
{
    int did = 1;
    for(int i=2; i<=31; i++)
        if(D[i].suvenyrai >= D[did].suvenyrai && D[i].negamino < D[did].negamino)
            did = i;

    return did;
}

void rasymas(diena D[])
{
    ofstream fr("savanoryste_rez.txt");

    int did = pagamino_daugiausia(D);

    for(int i=1; i<=31; i++)
        if(D[i].suvenyrai == D[did].suvenyrai && D[i].negamino == D[did].negamino)
            fr<<i<<" "<<D[i].laikas<<"\n";

    fr.close();
}
