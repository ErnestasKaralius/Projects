#include <fstream>
using namespace std;

struct mokinys {
    string vardas;
    string dalykas;
    double vidurkis=0;
};

struct dalykas {
    string pavadinimas;
    int populiarumas=1;
};

void skaitymas(int&m, mokinys M[], int&d, dalykas D[]);
void dalyku_populiarumas(int&d, dalykas D[], int m, mokinys M[]);
void dalyku_rikiavimas(int d, dalykas D[]);
bool ar_tinka_vidurkiai(int d, dalykas D[]);
void rasymas(int m, mokinys M[], int d, dalykas D[]);

int main()
{
    int m; // Mokinių skaičius
    int d; // Dalykų skaičius
    mokinys M[50];
    dalykas D[50];

    skaitymas(m,M,d,D);
    dalyku_populiarumas(d,D,m,M);
    dalyku_rikiavimas(d,D);
    rasymas(m,M,d,D);

    return 0;
}

void skaitymas(int&m, mokinys M[], int&d, dalykas D[])
{
    int sk; // Pažymių skaičius
    double p; // Pažymys
    ifstream fd("apklausa_data.txt");

    fd>>m;
    d = m;
    for(int i=0; i<m; i++)
    {
        fd>>M[i].vardas>>M[i].dalykas;
        D[i].pavadinimas = M[i].dalykas;

        fd>>sk;
        for(int j=0; j<sk; j++)
        {
            fd>>p;
            M[i].vidurkis += p;
        }
        M[i].vidurkis /= sk;
    }

    fd.close();
}

void dalyku_populiarumas(int&d, dalykas D[], int m, mokinys M[])
{
    // Pasikartojančių dalykų šalinimas
    for(int i=0; i<d-1; i++)
        for(int j=i+1; j<d; j++)
            if(D[i].pavadinimas == D[j].pavadinimas)
            {
                D[i].populiarumas++;
                D[j] = D[d-1];
                d--;
                j--;
            }

    //Jei mokinys turi netinkamą vidurkį, dalyko populiarumas mažinamas
    for(int i=0; i<d; i++)
        for(int j=0; j<m; j++)
            if(D[i].pavadinimas == M[j].dalykas && M[j].vidurkis < 9)
                D[i].populiarumas--;
}

void dalyku_rikiavimas(int d, dalykas D[])
{
    for(int i=0; i<d-1; i++)
        for(int j=i+1; j<d; j++)
        {
            if(D[i].populiarumas < D[j].populiarumas)
                swap(D[i],D[j]);

            else if(D[i].populiarumas == D[j].populiarumas)
                    if(D[i].pavadinimas > D[j].pavadinimas)
                        swap(D[i],D[j]);
        }
}

bool ar_tinka_vidurkiai(int d, dalykas D[])
{
    for(int i=0; i<d; i++)
        if(D[i].populiarumas != 0)
            return true;

    return false;
}

void rasymas(int m, mokinys M[], int d, dalykas D[])
{
    ofstream fr("apklausa_rez.txt");

    if(ar_tinka_vidurkiai(d,D))
        for(int i=0; i<d; i++)
        {
            if(D[i].populiarumas != 0)
            {
                fr<<D[i].pavadinimas<<" "<<D[i].populiarumas<<"\n";
                for(int j=0; j<m; j++)
                    if(M[j].dalykas == D[i].pavadinimas && M[j].vidurkis >= 9)
                        fr<<M[j].vardas<<"\n";
            }
        }
    else fr<<"Neatitinka vidurkis";

    fr.close();
}
