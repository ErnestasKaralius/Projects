#include <fstream>
using namespace std;

struct mokinys {
    char Vardas[16];
    int taskai;
};

void skaitymas(mokinys M[], int&n);
void rasymas(mokinys M[], int n);

int vidurkis(mokinys M[], int n, int sk);

int main()
{
    int n;
    mokinys M[30];
    mokinys A[30];

    skaitymas(M,n);
    rasymas(M,n);

    return 0;
}

void skaitymas(mokinys M[], int&n)
{
    ifstream fd("krepsininkai_data.txt");
    fd>>n;
    fd.ignore();
    for(int i=0; i<n; i++)
    {
        fd.get(M[i].Vardas, 16);
        fd>>M[i].taskai;
        fd.ignore();
    }
    fd.close();
}

int vidurkis(mokinys M[], int n, int sk)
{
    int suma=0;
    int kiekis=0;
    for(int i=0; i<n; i++)
        if(M[i].taskai >= sk )
        {
            suma+=M[i].taskai;
            kiekis++;
        }

    return suma/kiekis;
}

void rasymas(mokinys M[], int n)
{
    ofstream fr("krepsininkai_rez.txt");

    for(int i=0; i<n; i++)
        if(M[i].taskai >= 15) fr<<M[i].Vardas<<M[i].taskai<<"\n";

    fr<<"\nVisų mokinių taškų vidurkis: "<<vidurkis(M,n,0);
    fr<<"\nAtrinktų mokinių taškų vidurkis: "<<vidurkis(M,n,15);

    fr.close();
}
