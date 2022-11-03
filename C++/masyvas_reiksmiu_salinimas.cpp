#include <fstream>
using namespace std;

int main()
{
    int M[100]; // Skaičių masyvas
    int n; // Skaičių kiekis
    int i,j;
    ifstream fd("reiksmiu_salinimas_data.txt");
    ofstream fr("reiksmiu_salinimas_rez.txt");
    fd>>n;
    // Nuskaitymas
    for(i=0;i<n;i++) fd>>M[i];

    // Skaičius, kurį lyginsime su kitais
    for(i=0;i<n-1;i++)
        // Kiti skaičiai
        for(j=i+1;j<n;j++)
            if(M[i]==M[j])
            {
                // Pasikartojančio skaičiaus idėjimas į masyvo galą
                M[j]=M[n-1];
                n--;
                // Ar pakitusio masyvo j reikšmė vis dar lygi i
                if(M[i]==M[j])
                    j--; // Grįžimas prie senosios j reikšmės, kad iš naujo sukeistų masyvo reikšmių vietas
            }
    // Masyvo reikšmių išspausdinimas
    for(i=0;i<n;i++) fr<<M[i]<<" ";

    fd.close();
    fr.close();
    return 0;
}
