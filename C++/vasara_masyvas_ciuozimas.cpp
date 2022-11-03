#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int n; // Teisėjų skaičius
    double T[12],A[12]; // Technikos ir artistiškumo vertinimai
    double did,maz; // Didžiausia ir mažiausia reikšmė
    double suma; // Balų suma
    int i;
    ifstream fd("ciuozimas_data.txt");
    ofstream fr("ciuozimas_rez.txt");
    fd>>n;
    // Nuskaitymas
    for(i=0;i<n;i++) fd>>T[i]>>A[i];

    // Technikos vertinimas
    for(i=0;i<n;i++)
    {
        if(i==0) {did=T[i];maz=T[i];}
        if(T[i]>did) did=T[i];
        if(T[i]<maz) maz=T[i];
        suma=suma+T[i];
    }
    fr<<fixed<<setprecision(1)<<(suma-did-maz)/(n-2)<<endl;
    suma=0;

    // Artistiškumo vertinimas
    for(i=0;i<n;i++)
    {
        if(i==0) {did=A[i];maz=A[i];}
        if(A[i]>did) did=A[i];
        if(A[i]<maz) maz=A[i];
        suma=suma+A[i];
    }
    fr<<(suma-did-maz)/(n-2);

    fd.close();
    fr.close();
    return 0;
}
