#include <fstream>
using namespace std;

int main()
{
    double P[100]; // Prekių masyvas
    int n; // Prekių skaičius
    int sk; // Kaina
    int kiekis=1; // Pasikartojančių kainų kiekis
    int i,j;
    ifstream fd("prekiu_kaina_data.txt");
    ofstream fr("prekiu_kaina_rez.txt");
    fd>>n;
    for(i=0;i<n;i++)
    {
        fd>>sk;
        P[i]=sk; // Litų idėjimas į masyvą

        fd>>sk;
        P[i]=P[i]+(double)sk/100; // Centų idėjimas į masyvą
    }

    // Rikiavimas mažėjimo tvarka
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if(P[i]<P[j]) swap(P[i],P[j]);

    for(i=0;i<n;i++) fr<<P[i]<<endl;

    // Pasikartojančių kainų kiekio radimas
    for(i=1;i<n;i++) if(P[0]==P[i]) kiekis++;

    fr<<P[0]<<" kartojasi kartų: "<<kiekis;

    fd.close();
    fr.close();
    return 0;
}
