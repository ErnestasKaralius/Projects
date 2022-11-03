#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    char V[49][23]; // Vardai
    int T[12]; // Pažymiai
    double VD[49]; // Vidurkiai
    int n,m; // Mokinių skaičius, pažymių skaičus
    double vidurkis(int m,int T[]);
    int kiekis(int n,double VD[],double sk);

    ifstream fd("talento_stipendijos_data.txt");
    ofstream fr("talento_stipendijos_rez.txt");
    fd>>n;
    fd.ignore();
    for(int i=0;i<n;i++)
    {
        fd.get(V[i],22); // Vardų įdėjimas į masyvą
        fd>>m; // Kiek pažymių
        for(int j=0;j<m;j++) fd>>T[j]; // Pažymių įdėjimas į masyvą
        fd.ignore();
        VD[i]=vidurkis(m,T); // Kiekvieno vaiko vidurkio radimas
        fr<<fixed<<setprecision(2)<<V[i]<<VD[i]<<endl;
    }
    double sk;
    fd>>sk;
    fr<<kiekis(n,VD,sk); // Kiek mokinių gaus stipendija

    fd.close();
    fr.close();
    return 0;
}

// Vidurkio skaičiavimas
double vidurkis(int m,int T[])
{
    int suma=0;
    for(int j=0;j<m;j++) suma=suma+T[j];
    double v=(double)suma/m;

    return v;
}

// Kiek studentų gaus stipendijas
int kiekis(int n,double VD[],double sk)
{
    int kiekis=0;
    for(int j=0;j<n;j++) if(VD[j]>=sk) kiekis++;

    return kiekis;
}
