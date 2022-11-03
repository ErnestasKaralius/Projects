#include <fstream>
using namespace std;

int main()
{
    int K[100]; // Prekių kainų masyvas
    int n; // Prekių kainų skaičius;
    int l,c; // Litai ir centai
    int kiek=0; // Pasikartojančių kainų kiekis
    int i,j;
    ifstream fd("prekes_data.txt");
    ofstream fr("prekes_rez.txt");
    fd>>n;
    // Nuskaitymas
    for(i=0;i<n;i++)
    {
        fd>>l>>c;
        c=60*l+c; // Vertimas centais
        K[i]=c;
    }
    // Rikiavimas mažėjimo tvarka
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if(K[i]>K[j]) swap(K[j],K[i]);

    // Pasikartojančių kainų kiekio radimas
    for(i=0;i<n;i++) if(K[0]==K[i]) kiek++;
    fr<<kiek;
    fd.close();
    fr.close();
    return 0;
}
