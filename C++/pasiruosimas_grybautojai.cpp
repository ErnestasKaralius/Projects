#include <fstream>
using namespace std;

struct grybautojas {
    char Vardas[16];
    int baravykai;
    int raudonikiai;
    int lepsiai;
    int viso;
};

void skaitymas(int&n, grybautojas G[]);
int geriausias_rezultatas(int n, grybautojas G[]);
void rasymas(int n, grybautojas G[]);

int main()
{
    int n;
    grybautojas G[100];

    skaitymas(n,G);
    rasymas(n,G);

    return 0;
}

void skaitymas(int&n, grybautojas G[])
{
    ifstream fd("grybautojai_data.txt");
    int sk,d;

    fd>>n;
    fd.ignore();

    // Nulinimas
    for(int i=0; i<n; i++)
    {
        G[i].baravykai = 0;
        G[i].raudonikiai = 0;
        G[i].lepsiai = 0;
    }

    for(int i=0; i<n; i++)
    {
        fd.get(G[i].Vardas, 15);

        // Grybų rūšių sudėjimas
        fd>>d;
        for(int j=0; j<d; j++)
        {
            fd>>sk;
            G[i].baravykai += sk;

            fd>>sk;
            G[i].raudonikiai += sk;

            fd>>sk;
            G[i].lepsiai += sk;
        }
        G[i].viso = G[i].lepsiai + G[i].raudonikiai + G[i].baravykai;

        fd.ignore();
    }

    fd.close();
}

int geriausias_rezultatas(int n, grybautojas G[])
{
    int did=0;

    for(int i=1; i<n; i++)
        if(G[i].viso > G[did].viso)
            did = i;

    return did;
}

void rasymas(int n, grybautojas G[])
{
    ofstream fr("grybautojas_rez.txt");

    for(int i=0; i<n; i++)
        fr<<G[i].Vardas<<" "<<G[i].baravykai<<" "<<G[i].raudonikiai<<" "<<G[i].lepsiai<<endl;

    int geriausias = geriausias_rezultatas(n,G);
    fr<<G[geriausias].Vardas<<" "<<G[geriausias].viso;

    fr.close();
}
