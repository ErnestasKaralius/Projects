#include <fstream>
using namespace std;

int patiekalo_kaina(int n, int N[], int NK[]);
int pietu_kaina(int p, int K[]);

int main()
{
    int n, p; // Produktų ir patiekalų skaičiai
    int N[10]; // Produkto rūšies kaina

    char P[12][16]; // Pavadinimas
    int NK[10]; // Kiekis
    int K[12]; // Kaina

    ifstream fd("gimtadienis_data.txt");
    fd>>n>>p;
    for(int i=0; i<n; i++) fd>>N[i];
    fd.ignore();

    for(int i=0; i<p; i++)
    {
        fd.get(P[i],16);
        for(int j=0; j<n; j++) fd>>NK[j];
        K[i]=patiekalo_kaina(n,N,NK);
        fd.ignore();
    }
    fd.close();

    ofstream fr("gimtadienis_rez.txt");
    for(int i=0; i<p; i++) fr<<P[i]<<K[i]<<endl;

    int centai=pietu_kaina(p,K);
    fr<<centai/100<<" "<<centai%100;

    fr.close();

    return 0;
}

int patiekalo_kaina(int n, int N[], int NK[])
{
    int suma=0;
    for(int i=0; i<n; i++) suma=suma+NK[i]*N[i];

    return suma;
}

int pietu_kaina(int p, int K[])
{
    int suma=0;
    for(int i=0; i<p; i++) suma=suma+K[i];

    return suma;
}
