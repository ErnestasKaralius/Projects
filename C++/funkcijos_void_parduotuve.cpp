#include <fstream>
#include <iomanip>
using namespace std;

void skaitymas(int&n, int&gl, int S[], double K[], int G[]);
void rasymas(int n, int gl, int S[], double K[], int G[]);

void salinimas(int&i, int&n, int S[], double K[], int G[]);

int main()
{
    int n; // Prekių skaičius
    int gl; // Galiojimo laikas
    int S[199]; // Prekės kiekis
    double K[199]; // Prekės kaina
    int G[199]; // Prekės galiojimo laikas

    skaitymas(n,gl,S,K,G);
    rasymas(n,gl,S,K,G);

    return 0;
}

void skaitymas(int&n, int&gl, int S[], double K[], int G[])
{
    ifstream fd("prekiu_parduotuve_data.txt");
    fd>>n>>gl;
    for(int i=0;i<n;i++) fd>>S[i]>>K[i]>>G[i];

    fd.close();
}

void salinimas(int&i, int&n, int S[], double K[], int G[])
{
    for(int j=i;j<n-1;j++)
    {
        S[j]=S[j+1];
        K[j]=K[j+1];
        G[j]=G[j+1];
    }
    i--;
    n--;
}


void rasymas(int n, int gl, int S[], double K[], int G[])
{
    ofstream fr("prekiu_parduotuve_rez.txt");
    int pk=n; // Pradinis kiekis;
    int prekes=0; // Išimtų prekių kiekis
    double nuostoliai=0; // Patirti nuostoliai

    // Šalinimas
    for(int i=0;i<n;i++)
        if(G[i]<=gl)
        {
            prekes=prekes+S[i];
            nuostoliai=nuostoliai+K[i]*S[i];
            salinimas(i,n,S,K,G);
        }

    // Lentelė
    for(int i=0;i<58;i++) fr<<"-";
    fr<<"\n| Prekių kiekis | Prekės kaina | Prekės galiojimo laikas |\n";
    for(int i=0;i<58;i++) fr<<"-";
    for(int i=0;i<n;i++)
    {
        int sk=S[i]/10;
        int kiekis=0;
        while(sk!=0) {sk=sk/10;kiekis++;}

        fr<<"\n|"<<S[i]<<setw(15-kiekis)<<"|"<<setw(14)<<K[i]<<"|"<<setw(25)<<G[i]<<"|";
    }
    fr<<"\n";
    for(int i=0;i<58;i++) fr<<"-";

    fr<<"\nPasibaigė galiojimo laikas rūšims: "<<pk-n;
    fr<<"\nIšimtos iš prekybos prekės: "<<prekes;
    fr<<"\nParduotuvė patirs nuostolių: "<<nuostoliai<<" Lt";


    fr.close();
}
