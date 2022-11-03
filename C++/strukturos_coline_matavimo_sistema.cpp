#include <fstream>
using namespace std;

struct ilgis {
    int coliai;
    int pedos;
    int jardai;
};

void skaitymas(ilgis&a, ilgis&b);
void rasymas(ilgis c);

void sudetis(ilgis a, ilgis b, ilgis&c);
double metrai(ilgis c);


int main()
{
    ilgis a,b,c;

    skaitymas(a,b);
    sudetis(a,b,c);
    rasymas(c);

    return 0;
}

void skaitymas(ilgis&a, ilgis&b)
{
    ifstream fd("coline_matavimo_sistema_data.txt");

    fd>>a.coliai>>a.pedos>>a.jardai;
    fd>>b.coliai>>b.pedos>>b.jardai;

    fd.close();
}

void sudetis(ilgis a, ilgis b, ilgis&c)
{
    c.coliai = (a.coliai + b.coliai)%12;
    c.pedos = (a.pedos + b.pedos + (a.coliai + b.coliai)/12)%3;
    c.jardai = a.jardai + b.jardai + (a.pedos + b.pedos + (a.coliai + b.coliai)/12)/3;
}

double metrai(ilgis c)
{
    double m =(c.jardai * 36 + c.pedos * 3 + c.coliai) * 0.0254;

    return m;
}

void rasymas(ilgis c)
{
    ofstream fr("coline_matavimo_sistema_rez.txt");

    fr<<c.coliai<<" "<<c.pedos<<" "<<c.jardai<<endl;
    fr<<metrai(c);

    fr.close();
}
