#include <fstream>
using namespace std;

int main()
{
    char V[30][11],P[30][16]; // Vardų ir pavardžių masyvai
    int PP[30]; // Praleistų pamokų skaičiaus masyvas
    int n; // Mokinių skaičius
    int maz,did; // Mažiausias ir didžiausias praleistų pamokų skaičius
    int suma=0; // Praleistų pamokų suma
    int i;
    ifstream fd("char_mokiniai_data.txt");
    ofstream fr("char_mokiniai_rez.txt");
    fd>>n;
    fd.ignore();
    // Duomenų nuskaitymas
    for(i=0;i<n;i++)
    {
        fd.get(V[i],11); // Vardai
        fd.get(P[i],16); // Pavardės
        fd>>PP[i];
        suma=suma+PP[i];
        fd.ignore();
    }
    // Mažiausio ir didžiausio praleistų pamokų skaičiaus radimas
    maz=PP[0];
    did=PP[0];
    for(i=0;i<n;i++)
    {
        if(PP[i]<maz) maz=PP[i];
        if(PP[i]>did) did=PP[i];
    }
    fr<<"Praleido mažiausiai pamokų:\n";
    for(i=0;i<n;i++) if(PP[i]==maz) fr<<V[i]<<P[i]<<PP[i]<<endl;

    fr<<"\nPraleido dugiausiai pamokų:\n";
    for(i=0;i<n;i++) if(PP[i]==did) fr<<V[i]<<P[i]<<PP[i]<<endl;

    fr<<"\nVidutiniškai praleido pamokų: "<<suma/n;

    fd.close();
    fr.close();
    return 0;
}
