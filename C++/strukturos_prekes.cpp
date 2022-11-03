#include <fstream>
using namespace std;

struct preke {
    char Pavadinimas[21];
    double kaina;
    double kiekis;
};

void skaitymas(preke&a, preke&b, preke&c);
void rasymas(preke did);

void lyginimas(preke a, preke b, preke c, preke&did);

int main()
{
    preke a,b,c,did;

    skaitymas(a,b,c);
    lyginimas(a,b,c,did);
    rasymas(did);

    return 0;
}

void skaitymas(preke&a, preke&b, preke&c)
{
    ifstream fd("parduotuves_prekes_data.txt");
    fd.get(a.Pavadinimas,21); fd>>a.kaina>>a.kiekis;
    fd.ignore();
    fd.get(b.Pavadinimas,21); fd>>b.kaina>>b.kiekis;
    fd.ignore();
    fd.get(c.Pavadinimas,21); fd>>c.kaina>>c.kiekis;

    fd.close();
}

void lyginimas(preke a, preke b, preke c, preke&did)
{
    did=a;
    if(b.kaina*b.kiekis > did.kaina*did.kiekis) did=b;
    if(c.kaina*c.kiekis > did.kaina*did.kiekis) did=c;
}

void rasymas(preke did)
{
    ofstream fr("parduotuves_prekes_rez.txt");
    fr<<"Brangiausia prekė: "<<did.Pavadinimas;

    fr.close();
}
