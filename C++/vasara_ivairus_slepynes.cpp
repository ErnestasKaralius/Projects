#include <fstream>
using namespace std;

int main()
{
    int n,k,nr; // Pradinis vaikų skaičius, žodžių skaičius, atbėgusio vaiko numeris
    int V[25],M[25]; // Vaikų masyvas
    int kiek; // Kiek liko skaičių
    int i,j=0;
    ifstream fd("slepynes_data.txt");
    ofstream fr("slepynes_rez.txt");
    fd>>n>>k>>nr;
    // Nuskaitymas į masyvą
    for(i=0;i<n;i++) fd>>V[i];
    V[n]=nr;
    n++;
    kiek=n;
    for(i=0;i<n;i++) M[i]=V[i];

    // Iki tol, kol liks tik vienas skaičius
    while(kiek!=1)
    {
        // Nuo išjėusio žmogaus iki žodžių skaičiaus
        for(i=j;i<k;i++)
            // Grįžimas atgal į masyvo pradžią
            if(j!=kiek&&i!=0&&j!=kiek-1) j++;
                else j=0;

        // Masyvo reikšmės šalinimas
        for(i=j;i<kiek;i++) V[i]=V[i+1];
        kiek--; // Kiekio mažinimas
    }

    // Naujo vaiko įterpimas į masyvą
    for(i=0;i<n;i++)
        if(M[i]==V[0])
            for(j=n-1;j>i;j--) swap(M[j],M[j-1]);

    // Išspausdinimas
    for(i=0;i<n;i++) fr<<M[i]<<" ";

    fd.close();
    fr.close();
    return 0;
}
