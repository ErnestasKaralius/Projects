#include <fstream>
#include <string>
using namespace std;

struct miestas {
    char Pavadinimas[21];
    string Valstybe;
    int kiekis;
};

void skaitymas(int&n, miestas M[]);
void salinimas(int&n, miestas M[]);
void rasymas(int n, miestas M[]);


int main()
{
    int n;
    miestas M[300];

    skaitymas(n,M);
    salinimas(n,M);
    rasymas(n,M);

    return 0;
}

void skaitymas(int&n, miestas M[])
{
    ifstream fd("miestai_data.txt");

    fd>>n;
    fd.ignore();
    for(int i=0; i<n; i++)
    {
        fd.get(M[i].Pavadinimas, 21);
        getline(fd, M[i].Valstybe);
        M[i].kiekis=1;
    }

    fd.close();
}

void salinimas(int&n, miestas M[])
{
    for(int i=0; i<n-1; i++)
        for(int j=i+1; j<n; j++)
            if(M[i].Valstybe == M[j].Valstybe)
            {
                M[j]=M[n-1];
                n--;
                j--;

                M[i].kiekis++;
            }
}

void rasymas(int n, miestas M[])
{
    ofstream fr("miestai_rez.txt");

    for(int i=0; i<n; i++)
        fr<<M[i].Valstybe<<" "<<M[i].kiekis<<"\n";

    fr.close();
}





