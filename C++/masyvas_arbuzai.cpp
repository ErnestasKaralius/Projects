#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int sk,i; // Arbūzų skaičius
    double A[100]; // Arbūzų masyvas
    double suma=0,vid; // Suma, vidurkis
    double arbuzas; // Arbūzas, artimiausias vidurkiui
    int vieta; // Arbūzo, artimiausio vidurkiui, vieta
    ifstream fd("arbuzai_data.txt");
    ofstream fr("arbuzai_rez.txt");
    fd>>sk;

    // Nuskaitymas
    for(i=0;i<sk;i++) fd>>A[i];

    // Aritmetinio vidurkio skaičiavimas
    for(i=0;i<sk;i++) suma=suma+A[i];
    vid=suma/sk;

    // Arbūzo, artimiausio aritmetiniam vidurkiui, radimas
    arbuzas=A[0];
    vieta=1;
    for(i=1;i<sk;i++)
        if(A[i]>arbuzas&&A[i]<=vid||A[i]<arbuzas&&A[i]>=vid) arbuzas=A[i];

    fr<<fixed<<setprecision(2)<<vieta<<" "<<arbuzas;

    fd.close();
    fr.close();
    return 0;
}
