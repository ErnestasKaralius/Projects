#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

void skaitymas(int&n, int&m, int&k, string Isvyke[], string Naujokai[], string Ndalykai[], string Mokiniai[], string Dalykai[]);
void rasymas(int k, string Mokiniai[], string Dalykai[]);

void salinimas(int j, int k, string Mokiniai[], string Dalykai[]);
void iterpimas(int i,int k, string Naujokai[], string Ndalykai[], string Mokiniai[], string Dalykai[]);
void rikiavimas(int k, string Mokiniai[], string Dalykai[]);

int main()
{
    int n,m,k;
    string Isvyke[100];

    string Naujokai[100];
    string Ndalykai[100];

    string Mokiniai[200];
    string Dalykai[200];


    skaitymas(n,m,k,Isvyke,Naujokai,Ndalykai,Mokiniai,Dalykai);

    // Šalinami išvykę mokiniai
    for(int i=0; i<n; i++)
        for(int j=0; j<k; j++)
            if(Isvyke[i] == Mokiniai[j])
            {
                salinimas(j,k,Mokiniai,Dalykai);
                k--;
                j--;
            }

    // Naujų mokinių įterpimas
    for(int i=0; i<m; i++)
    {
        iterpimas(i,k,Naujokai,Ndalykai,Mokiniai,Dalykai);
        k++;
    }

    rikiavimas(k,Mokiniai,Dalykai);
    rasymas(k,Mokiniai,Dalykai);

    return 0;
}

void skaitymas(int&n, int&m, int&k, string Isvyke[], string Naujokai[], string Ndalykai[], string Mokiniai[], string Dalykai[])
{
    ifstream fd("klases_sarasas_data.txt");
    char Vardas[26];
    // Išvykusių mokinių nuskaitymas
    fd>>n;
    fd.ignore();
    for(int i=0; i<n; i++)
    {
        getline(fd, Isvyke[i], '*');
        fd.ignore();
    }
    // Naujokų nuskaitymas
    fd>>m;
    fd.ignore();
    for(int i=0; i<m; i++)
    {
        fd.get(Vardas, 26);
        Naujokai[i]=Vardas;
        fd>>Ndalykai[i];
        fd.ignore();
    }
    // Klasės sąrašo nuskaitymas
    fd>>k;
    fd.ignore();
    for(int i=0; i<k; i++)
    {
        fd.get(Vardas, 26);
        Mokiniai[i]=Vardas;
        fd>>Dalykai[i];
        fd.ignore();
    }
    fd.close();
}

void salinimas(int j, int k, string Mokiniai[], string Dalykai[])
{
    Mokiniai[j]=Mokiniai[k-1];
    Dalykai[j]=Dalykai[k-1];
}

void iterpimas(int i, int k, string Naujokai[], string Ndalykai[], string Mokiniai[], string Dalykai[])
{
    Mokiniai[k]=Naujokai[i];
    Dalykai[k]=Ndalykai[i];
}

void rikiavimas(int k, string Mokiniai[], string Dalykai[])
{
    for(int i=0; i<k-1; i++)
        for(int j=i+1; j<k; j++)
            if(Mokiniai[i][0] > Mokiniai[j][0])
            {
                swap(Mokiniai[i], Mokiniai[j]);
                swap(Dalykai[i], Dalykai[j]);
            }
}

void rasymas(int k, string Mokiniai[], string Dalykai[])
{
    ofstream fr("klases_sarasas_rez.txt");
    for(int i=0; i<32; i++) fr<<"-";
    fr<<"\nMokinys"<<setw(26)<<"Dalykas\n";
    for(int i=0; i<32; i++) fr<<"-";
    fr<<"\n";

    for(int i=0; i<k; i++) fr<<Mokiniai[i]<<Dalykai[i]<<"\n";
    for(int i=0; i<32; i++) fr<<"-";
    fr<<"\nPasirinko etiką\n";
    for(int i=0; i<32; i++) fr<<"-";
    fr<<"\n";

    for(int i=0; i<k; i++)
        if(Dalykai[i] == "Etika") fr<<Mokiniai[i]<<Dalykai[i]<<"\n";

    fr.close();
}
