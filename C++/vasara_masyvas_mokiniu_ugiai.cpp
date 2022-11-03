#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int n; // Mokinių skaičius
    int U[100]; // Ūgių masyvas
    int did,maz; // Didžiausias ir mažiausias ūgis
    int suma=0; // Ūgių suma
    double vid; // Ūgių vidurkis
    int i;
    ifstream fd("mokiniu_ugiai_data.txt");
    ofstream fr("mokiniu_ugiai_rez.txt");
    fd>>n;
    // Nuskaitymas
    for(i=0;i<n;i++) fd>>U[i];

    // Didžiausio ir mažiausio ūgio radimas, sumos skaičiavimas
    did=maz=U[0];
    for(i=0;i<n;i++)
    {
        suma=suma+U[i];
        if(U[i]>did) did=U[i];
        if(U[i]<maz) maz=U[i];
    }

    // Ūgių vidurkis
    vid=(double)suma/n;

    fr<<"Didžiausias ūgis: "<<did<<endl;
    fr<<"Mažiausias ūgis: "<<maz<<endl;
    fr<<fixed<<setprecision(2)<<"Vidutinis ūgis: "<<vid<<endl;
    fr<<"Viršijo vidurkį ūgiai: ";
        for(i=0;i<n;i++) if(U[i]>vid) fr<<U[i]<<" ";

    fd.close();
    fr.close();
    return 0;
}
