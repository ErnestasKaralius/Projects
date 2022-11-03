#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int n,i; // Mokinių skaičius
    int N[100]; // Ūgių masyvas
    int maz,did; // Mažiausias ir didžiausias skaičius
    int suma=0; // Suma
    double vid; // Vidurkis
    ifstream fd("salinimas_ugiai_data.txt");
    ofstream fr("salinimas_ugiai_rez.txt");
    fd>>n;
    // Nuskaitymas
    for(i=0;i<n;i++) fd>>N[i];

    // Didžiausio ir mažiausio skaičių radimas
    for(i=0;i<n;i++)
    {
        if(i==0) {maz=N[i]; did=N[i];}
        if(N[i]<maz) maz=N[i];
        if(N[i]>did) did=N[i];
    }

    // Ūgių vidurkio skaičiavimas
    for(i=0;i<n;i++) suma=suma+N[i];
    vid=(double)suma/n;

    for(i=0;i<n;i++)
        if(N[i]<vid)
        {
            N[i]=N[n-1];
            n--;
            i--;
        }

    fr<<"Didžiausias ūgis: "<<did<<endl;
    fr<<"Mažiausias ūgis: "<<maz<<endl;
    fr<<fixed<<setprecision(2)<<"Vidutinis ūgis: "<<vid<<endl;
    fr<<"Viršijantys vidurkį ūgiai: ";
    for(i=0;i<n;i++) fr<<N[i]<<" ";

    fd.close();
    fr.close();
    return 0;
}
