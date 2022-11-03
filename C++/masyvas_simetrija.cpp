#include <fstream>
using namespace std;

int main()
{
    int n,i; // Sveikųjų skaičių kiekis
    int M[100]; // Skaičių masyvas
    bool t=1; // Seka yra simetrinė
    int kiek=0;
    ifstream fd("simetrija_data.txt");
    ofstream fr("simetrija_rez.txt");
    fd>>n;
    // Nuskaitymas
    for(i=0;i<n;i++) fd>>M[i];

    // Ar masyvų reikšmės yra simetriškos
    for(i=0;i<n/2;i++) if(M[i]==M[n-1-i]) kiek++;

    if(kiek==n/2) fr<<"TAIP";
        else fr<<"NE";

    fd.close();
    fr.close();
    return 0;
}
