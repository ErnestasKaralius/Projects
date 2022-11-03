#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int n; // Prekių skaičius
    int d; // Data
    int S[198],G[198]; // Prekių kiekis, galiojimo laikas
    double K[198]; // Prekės kaina
    int kiek=0; // Pasibaigusių galiojimų kiekis
    int p=0; // Kiek reikės išimti prekių
    double nuost=0; // Nuostoliai
    int i,j,sk;
    ifstream fd("maisto_parduotuve_data.txt");
    ofstream fr("maisto_parduotuve_rez.txt");
    fd>>n>>d;
    for(i=0;i<n;i++) fd>>S[i]>>K[i]>>G[i];

    for(i=0;i<n;i++)
        if(G[i]<d)
        {
            kiek++;
            nuost=nuost+S[i]*K[i];
            p=p+S[i];
            for(j=i;j<n-1;j++)
            {
                S[j]=S[j+1];
                K[j]=K[j+1];
                G[j]=G[j+1];
            }
            n--;
            i--;
        }

    fr<<"Prekės prekyboje\n";
    for(i=0;i<51;i++) fr<<'-';
    fr<<"\n| Prekių kiekis | Prekės kaina | Galiojimo laikas |\n";
    for(i=0;i<n;i++)
    {
        sk=S[i]/10;j=0;
        while(sk!=0) {sk=sk/10;j++;}
        fr<<'|'<<S[i]<<setw(15-j)<<'|'<<setw(14)<<K[i]<<'|'<<setw(18)<<G[i]<<'|'<<endl;
    }
    for(i=0;i<51;i++) fr<<'-'; fr;
    fr<<"\nPasibaigė rūšių galiojimo laikas: "<<kiek;
    fr<<"\nIšimti iš prekybos reikės prekių: "<<p;
    fr<<"\nParduotuvė patirs nuostolių: "<<nuost<<" Lt";



    fd.close();
    fr.close();
    return 0;
}
