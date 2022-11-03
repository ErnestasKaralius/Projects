#include <fstream>
using namespace std;

struct respondentas {
    char Vardas[26];
    int amzius;
    char lytis;
    char grupe;
};

void skaitymas(int&n, respondentas R[]);
void bedarbiu_atrinkimas(char g, int n, respondentas R[], int&k, respondentas B[]);
void rikiavimas(int k, respondentas B[]);
void salinimas(int&k, respondentas B[]);
void rasymas(int k, respondentas B[]);

int main()
{
    int n;
    respondentas R[999];
    int k;
    respondentas B[999];

    skaitymas(n,R);
    bedarbiu_atrinkimas('b',n,R,k,B);
    rasymas(k,B);

    return 0;
}

void skaitymas(int&n, respondentas R[])
{
    ifstream fd("darbuotojai.dat");

    fd>>n;
    fd.ignore();
    for(int i=0; i<n; i++)
    {
        fd.get(R[i].Vardas, 25);
        fd>>R[i].amzius;
        fd>>R[i].lytis;
        fd>>R[i].grupe;
        fd.ignore();
    }

    fd.close();
}

void bedarbiu_atrinkimas(char g, int n, respondentas R[], int&k, respondentas B[])
{
    k=0;
    for(int i=0; i<n; i++)
        if(R[i].grupe == g)
        {
            B[k] = R[i];
            k++;
        }
}

void rikiavimas(int k, respondentas B[])
{
    for(int i=0; i<k-1; i++)
        for(int j=i+1; j<k; j++)
            if(B[i].amzius > B[j].amzius)
                swap(B[i], B[j]);
}

void salinimas(int&k, respondentas B[])
{
    for(int i=0; i<k; i++)
        if(B[i].lytis == 'm')
        {
            for(int j=i; j<k-1; j++)
                B[j]=B[j+1];

            k--;
            i--;
        }
}

void rasymas(int k, respondentas B[])
{
    ofstream fr("darbuotojai_rez.dat");

    rikiavimas(k,B);
    for(int i=0; i<k; i++)
        fr<<B[i].Vardas<<" "<<B[i].amzius<<" "<<B[i].lytis<<endl;

    fr<<"\n";

    salinimas(k,B);
    for(int i=0; i<k; i++)
        fr<<B[i].Vardas<<" "<<B[i].amzius<<" "<<B[i].lytis<<endl;

    fr.close();
}
