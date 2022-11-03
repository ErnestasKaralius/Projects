#include <fstream>
#include <iomanip>
using namespace std;

struct degalai {
    char Pavadinimas[16];
    double bk; // Benzino litro kaina
    double dk; // Dujø litro kaina
};

void skaitymas(double&b, double&d, double&m, int&n, degalai D[]);
void rasymas(double b, double d, double m, int n, degalai D[]);

double kaina(double b, double m, double k);

int main()
{
    double b,d;
    double m;
    int n;

    degalai D[100];

    skaitymas(b,d,m,n,D);
    rasymas(b,d,m,n,D);

    return 0;
}

void skaitymas(double&b, double&d, double&m, int&n, degalai D[])
{
    ifstream fd("islaidos_data.txt");
    fd>>b>>d>>m>>n;
    fd.ignore();
    for(int i=0; i<n; i++)
    {
        fd.get(D[i].Pavadinimas, 16); fd>>D[i].bk>>D[i].dk;
        fd.ignore();
    }

    fd.close();
}

double kaina(double b, double m, double k)
{
    double suma=m/100*b * k;

    return suma;
}

void rasymas(double b, double d, double m, int n, degalai D[])
{
    ofstream fr("islaidos_rez.txt");

    for(int i=0; i<n; i++)
        fr<<fixed<<setprecision(2)<<D[i].Pavadinimas<<kaina(b,m,D[i].bk)<<" "<<kaina(d,m,D[i].dk)<<endl;

    fr.close();
}
