#include <fstream>
using namespace std;

struct takas {
    string pavadinimas;
    int laikas;
};

void skaitymas(int&n, takas T[]);
void salinimas(int&n, takas T[]);
void rikiavimas(int n, takas T[]);
void rasymas(int n, takas T[]);

int main()
{
    int n;
    takas T[30];

    skaitymas(n,T);
    salinimas(n,T);
    rikiavimas(n,T);
    rasymas(n,T);

    return 0;
}

void skaitymas(int&n, takas T[])
{
    char v[21];
    ifstream fd("takai_data.txt");

    fd>>n;
    fd.ignore();
    for(int i=0; i<n; i++)
    {
        fd.get(v,21);
        T[i].pavadinimas = v;
        fd>>T[i].laikas;
        fd.ignore();
    }

    fd.close();
}

void salinimas(int&n, takas T[])
{
    for(int i=0; i<n-1; i++)
        for(int j=i+1; j<n; j++)
            if(T[j].pavadinimas == T[i].pavadinimas)
            {
                T[i].laikas += T[j].laikas;

                swap(T[j],T[n-1]);
                n--;
                j--;
            }
}

void rikiavimas(int n, takas T[])
{
    for(int i=0; i<n-1; i++)
        for(int j=i+1; j<n; j++)
        {
            if(T[i].laikas < T[j].laikas)
                swap(T[i],T[j]);

            else if(T[i].laikas == T[j].laikas)
                if(T[i].pavadinimas > T[j].pavadinimas)
                    swap(T[i],T[j]);
        }
}

void rasymas(int n, takas T[])
{
    ofstream fr("takai_rez.txt");

    for(int i=0; i<n; i++)
        fr<<T[i].pavadinimas<<" "<<T[i].laikas<<"\n";

    fr.close();
}
