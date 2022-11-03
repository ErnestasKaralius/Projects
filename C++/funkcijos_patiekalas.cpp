#include <fstream>
#include <iomanip>
using namespace std;
double mases_dalis(double rkiekis,double bkiekis,double akiekis,int mkiekis);

int main()
{
    int n; // Produktų skaičius
    int m; // Produkto masė
    double r,b,a; // Riebalų, baltymų, angliavandenių kiekis produkte
    double rkiekis=0,bkiekis=0,akiekis=0; // Riebalų, baltymų, angliavandenių bendras kiekis patekale
    int mkiekis=0; // Patiekalo masė
    ifstream fd("funkcijos_patiekalas_data.txt");
    fd>>n;
    for(int i=0;i<n;i++)
    {
        fd>>r>>b>>a>>m;
        rkiekis=rkiekis+r;
        bkiekis=bkiekis+b;
        akiekis=akiekis+a;
        mkiekis=mkiekis+m;
    }
    mases_dalis(rkiekis,bkiekis,akiekis,mkiekis);

    fd.close();
    return 0;
}

double mases_dalis(double rkiekis,double bkiekis,double akiekis,int mkiekis)
{
    ofstream fr("funkcijos_pateikalas_rez.txt");
    fr<<fixed<<setprecision(2)<<rkiekis/mkiekis*100<<endl;
    fr<<bkiekis/mkiekis*100<<endl;
    fr<<akiekis/mkiekis*100;

    fr.close();

    return 1;
}


