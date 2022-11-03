#include <fstream>
#include <iomanip>
using namespace std;
double bilietu_kaina(double kaina,int nariai);

int main()
{
    double k,kelias,kk; // Kiek sunaudoja 100km degalų, kelionės kelio ilgis, keik kaioja degalai
    int nariai; // Ðeimos narių skaièius
    ifstream fd("funkcijos_kelione_data.txt");
    ofstream fr("funkcijos_kelione_rez.txt");
    fd>>k>>kelias>>kk>>nariai;
    double degalu_kaina=k/100*kelias*kk; // Kiek kainuoja degalai

    double sk,kaina; // Maršrutų skaičius, kiekvieno maršruto kaina
    fd>>sk;
    for(int i=0;i<sk;i++)
    {
        fd>>kaina;
        fr<<fixed<<setprecision(2)<<degalu_kaina-bilietu_kaina(kaina,nariai)<<endl; // Degalų ir bilietų kainos skirtumas
    }

    fd.close();
    fr.close();
    return 0;
}

double bilietu_kaina(double kaina,int nariai)
{
    double bk=kaina*nariai; // Kiekvieno maršruto bilietų kaina šeimai

    return bk;
}
