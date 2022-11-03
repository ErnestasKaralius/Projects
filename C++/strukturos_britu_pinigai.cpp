#include <fstream>
using namespace std;

struct pinigai {
    int svaras;
    int silingas;
    int pensas;
};

void skaitymas(pinigai&a, pinigai&b);
void sudeti(pinigai a, pinigai b, pinigai&c);
void rasymas(pinigai c);

int main()
{
    pinigai a,b,c;

    skaitymas(a,b);
    sudeti(a,b,c);
    rasymas(c);

    return 0;
}

void skaitymas(pinigai&a, pinigai&b)
{
    ifstream fd("strukturos_britu_pinigai_data.txt");

    fd>>a.svaras>>a.silingas>>a.pensas;
    fd>>b.svaras>>b.silingas>>b.pensas;

    fd.close();
}

void sudeti(pinigai a, pinigai b, pinigai&c)
{
    c.pensas = (a.pensas + b.pensas)%12;
    c.silingas = (a.silingas + b.silingas + (a.pensas + b.pensas)/12)%20;
    c.svaras = a.svaras + b.svaras + (a.silingas + b.silingas + (a.pensas + b.pensas)/12)/20;
}

void rasymas(pinigai c)
{
    ofstream fr("strukturos_britu_pinigai_rez.txt");

    fr<<c.svaras<<" "<<c.silingas<<" "<<c.pensas;

    fr.close();
}



















