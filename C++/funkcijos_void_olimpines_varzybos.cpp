#include <fstream>
#include <iomanip>
using namespace std;

void skaitymas_salys(int&n, string Santrumpa[202], char Pavadinimas[][256]);
void skaitymas_plaukikai(char Vardas[][21], string Salis[], string Laikas[]);
void rasymas(int n, char Vardas[][21], char Pavadinimas[][256], string Salis[], string Santrumpa[], string Laikas[]);

string pilnas_pavadinimas(int n, string Salis[], int i, string Santrumpa[], char Pavadinimas[][256]);

int main()
{
    int n; // Šalių skaičius
    string Santrumpa[202];
    char Pavadinimas[202][256];

    char Vardas[202][21];
    string Salis[202];
    string Laikas[202];

    skaitymas_salys (n, Santrumpa, Pavadinimas);
    skaitymas_plaukikai (Vardas, Salis, Laikas);
    rasymas (n, Vardas, Pavadinimas, Salis, Santrumpa, Laikas);


    return 0;
}

void skaitymas_salys(int&n, string Santrumpa[202], char Pavadinimas[][256])
{
    ifstream fd("saliu_santrumpos_data.txt");
    fd>>n;
    fd.ignore();
    for(int i=0; i<n; i++)
    {
        fd>>Santrumpa[i];
        fd.ignore();
        fd.get(Pavadinimas[i],256);

        fd.ignore();
    }

    fd.close();
}

void skaitymas_plaukikai(char Vardas[][21], string Salis[], string Laikas[])
{
    ifstream fd("sportininku_data.txt");
    for(int i=0; i<8; i++)
    {
        fd.get(Vardas[i],21);
        fd>>Salis[i];
        fd>>Laikas[i];

        fd.ignore();
    }

    fd.close();
}

void rasymas(int n, char Vardas[][21], char Pavadinimas[][256], string Salis[], string Santrumpa[], string Laikas[])
{
    ofstream fr("sportininku_sarasas_rez.txt");
    for(int i=0; i<8; i++)
       fr<<Vardas[i]<<pilnas_pavadinimas(n, Salis, i, Santrumpa, Pavadinimas)<<setw(40)<<Laikas[i]<<endl;

    fr.close();
}

string pilnas_pavadinimas(int n, string Salis[], int i, string Santrumpa[], char Pavadinimas[][256])
{
    for(int j=0; j<n; j++)
        if(Salis[i] == Santrumpa[j]) return Pavadinimas[j];
}
