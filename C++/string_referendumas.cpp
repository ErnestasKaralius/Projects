#include <fstream>
#include <string>
using namespace std;

void skaitymas(int&n, string Duomenys[]);
void rasymas(int n, int pk, string Duomenys[]);

void salinimas(int j, int n, string Duomenys[]);

int main()
{
    int n; // Parašų kiekis
    int pk; // Pradinis parašų kiekis
    string Duomenys[100];

    skaitymas(n,Duomenys);
    pk=n;

    for(int i=0; i<n-1; i++)
        for(int j=i+1; j<n; j++)
            if(Duomenys[i] == Duomenys[j])
            {
                salinimas(j,n,Duomenys);
                n--;
                j--;
            }

    rasymas(n,pk,Duomenys);

    return 0;
}

void skaitymas(int&n, string Duomenys[])
{
    ifstream fd("referendumas_data.txt");
    fd>>n;
    fd.ignore();
    for(int i=0; i<n; i++) getline(fd, Duomenys[i]);

    fd.close();
}

void salinimas(int j, int n, string Duomenys[])
{
    for(int j; j<n-1; j++) Duomenys[j]=Duomenys[j+1];
}

void rasymas(int n, int pk, string Duomenys[])
{
    ofstream fr("referendumas_rez.txt");

    for(int i=0; i<30; i++) fr<<"-";
    fr<<"\nSąrašas\n";
    for(int i=0; i<30; i++) fr<<"-";
    fr<<"\n";

    for(int i=0; i<n; i++) fr<<Duomenys[i]<<endl;

    for(int i=0; i<30; i++) fr<<"-";
    fr<<"\nIšvada\n";
    for(int i=0; i<30; i++) fr<<"-";
    if(n<pk) fr<<"\nReferendumui parašų neužtenka.";
        else fr<<"\nReferendumui parašų užtenka.";

    fr.close();
}
