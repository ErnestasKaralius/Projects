#include <fstream>
using namespace std;

int main()
{
    double N[100],n; // Prekių kainos
    int p,i; // Pabrangimo procentai
    double suma=0,vid;
    ifstream fd("prekiu_branginimas_data.txt");
    ofstream fr("prekiu_branginimas_rez.txt");
    fd>>n>>p;
    p=1+p/100;
    // Nuskaitymas
    for(i=0;i<n;i++) fd>>N[i];

    // Sumos ir vidurkio skaičiavimas
    for(i=0;i<n;i++) suma=suma+N[i];
    vid=suma/n;

    // Skaičių, mažesnių už vidurkį, kainos didinimas
    for(i=0;i<n;i++) if(N[i]<vid) N[i]=N[i]*p;

    // Vidurkio po branginimo radimas
    for(i=0;i<n;i++) suma=suma+N[i];
    vid=suma/n;

    fr<<"Vidutinė kaina po branginimo: "<<vid;

    fd.close();
    fr.close();
    return 0;
}
