#include <fstream>
#include <iomanip>
using namespace std;

struct draugas {
    char Vardas[16];
    char valiuta;
    int pinigai;
    int centai;
};

void skaitymas(draugas&a, draugas&b, draugas&c);
void rasymas(draugas a, draugas b, draugas c);

double suma_doleriais(draugas t);
string turtingiausias_draugas(draugas a, draugas b, draugas c);

int main()
{
    draugas a,b,c;

    skaitymas(a,b,c);
    rasymas(a,b,c);

    return 0;
}

void skaitymas(draugas&a, draugas&b, draugas&c)
{
    ifstream fd("draugu_pinigai_data.txt");

    fd.get(a.Vardas, 16); fd>>a.valiuta>>a.pinigai>>a.centai;
    fd.ignore();
    fd.get(b.Vardas, 16); fd>>b.valiuta>>b.pinigai>>b.centai;
    fd.ignore();
    fd.get(c.Vardas, 16); fd>>c.valiuta>>c.pinigai>>c.centai;

    fd.close();
}

double suma_doleriais(draugas t)
{
    double suma;
    if(t.valiuta == 'e') suma = (t.pinigai + t.centai*0.01) * 1.13;
        else if(t.valiuta == 's') suma = (t.pinigai + t.centai*0.01) * 1.33;
            else suma = t.pinigai + t.centai*0.01;

    return suma;
}
string turtingiausias_draugas(draugas a, draugas b, draugas c)
{
    draugas did=a;
    if(suma_doleriais(b) > suma_doleriais(did)) did=b;
    if(suma_doleriais(c) > suma_doleriais(did)) did=c;

    return did.Vardas;
}

void rasymas(draugas a, draugas b, draugas c)
{
    ofstream fr("draugu_pinigai_rez.txt");

    fr<<"Turtingiausias draugas: "<<turtingiausias_draugas(a,b,c)<<endl;
    fr<<fixed<<setprecision(2)<<"Pinigų suma: "<<suma_doleriais(a) + suma_doleriais(b) + suma_doleriais(c)<<endl;
    fr<<"Pinigų vidurkis: "<<(suma_doleriais(a) + suma_doleriais(b)+ suma_doleriais(c))/3;

    fr.close();
}


