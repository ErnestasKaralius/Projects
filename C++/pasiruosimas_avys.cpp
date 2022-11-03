#include <fstream>
#include <string>
using namespace std;

struct avis {
    string vardas;
    char Fragmentas[21];
    int koeficientas;
};

void skaitymas(int&n, int&m, int&tiriama, avis A[]);
void koeficientu_radimas(int n, int m, avis A[]);
void rikiavimas(int n, avis A[]);
void rasymas(int n, avis A[]);

int main()
{
    int n, m; // Avių skaičius ir DNR ilgis
    int tiriama;
    avis A[20];

    skaitymas(n,m,tiriama,A);
    koeficientu_radimas(n,m,A);
    rikiavimas(n,A);
    rasymas(n,A);

    return 0;
}

void skaitymas(int&n, int&m, int&tiriama, avis A[])
{
    ifstream fd("avys_data.txt");

    char v[11];

    fd>>n>>m;
    fd>>tiriama;
    fd.ignore();

    for(int i=0; i<n; i++)
    {
        fd.get(v, 11);
        A[i].vardas = v;
        fd.ignore();

        fd.get(A[i].Fragmentas, m+1);
        fd.ignore();

        A[i].koeficientas=0;
    }
    swap(A[tiriama-1], A[0]); // Tiriamos avies įdėjimas į masyvo priekį

    fd.close();
}

void koeficientu_radimas(int n, int m, avis A[])
{
    for(int i=1; i<n; i++)
        for(int j=0; j<m; j++)
            if(A[i].Fragmentas[j] == A[0].Fragmentas[j]) // Jei sutamps raidės, koeficientas didėja
                A[i].koeficientas++;

}

void rikiavimas(int n, avis A[])
{
    for(int i=1; i<n-1; i++)
        for(int j=i+1; j<n; j++)
        {
            if(A[i].koeficientas < A[j].koeficientas)
                swap(A[i], A[j]);

            else if(A[i].koeficientas == A[j].koeficientas)
                if(A[i].vardas > A[j].vardas)
                    swap(A[i], A[j]);
        }
}

void rasymas(int n, avis A[])
{
    ofstream fr("avys_rez.txt");

    fr<<A[0].vardas<<"\n";

    for(int i=1; i<n; i++)
        fr<<A[i].vardas<<" "<<A[i].koeficientas<<"\n";


    fr.close();
}
