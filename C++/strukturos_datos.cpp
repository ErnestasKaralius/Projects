#include <fstream>
using namespace std;

struct data {
    int metai;
    int menesis;
    int diena;
};

void skaitymas(data&a, data&b, data&c);
void rasymas(data maz);

void maziausias(data a, data b, data c, data&maz);

int main()
{
    data a,b,c;
    data maz;

    skaitymas(a,b,c);
    maziausias(a,b,c,maz);
    rasymas(maz);

    return 0;
}

void skaitymas(data&a, data&b, data&c)
{
    ifstream fd("datos_data.txt");

    fd>>a.metai>>a.menesis>>a.diena;
    fd>>b.metai>>b.menesis>>b.diena;
    fd>>c.metai>>c.menesis>>c.diena;

    fd.close();
}

void maziausias(data a, data b, data c, data&maz)
{
    int la,lb,lc;
    la=a.metai*365 + a.menesis*30 + a.diena;
    lb=b.metai*365 + b.menesis*30 + b.diena;
    lc=c.metai*365 + c.menesis*30 + c.diena;

    maz=a;
    if(lb < la && lb < lc) maz=b;
        else if(lc < la && lc < lb) maz=c;
}

void rasymas(data maz)
{
    ofstream fr("datos_rez.txt");
    fr<<maz.metai<<" "<<maz.menesis<<" "<<maz.diena;

    fr.close();
}
