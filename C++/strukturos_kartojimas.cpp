#include <fstream>
#include <string>
#include <iostream>
using namespace std;

struct darbuotojas {
    string vardas;
    char Pavarde[26];
    int metai;
};

void skaitymas_darbuotojai(char darbuotoju_failas[], int&kiekis, darbuotojas D[]);

int main()
{
    char darbuotoju_failas[] = "darbuotojai_data.dat";
    char keitimu_failas[] = "keitimai_data.dat";
    char nauju_failas[] = "nauji_data.dat";
    char atleistu_failas[] = "atleisti_data.dat";

    int kiekis;
    darbuotojas D[100];

    int k;
    darbuotojas K[100];

    skaitymas_darbuotojai(darbuotoju_failas,kiekis,D);

    return 0;
}

void skaitymas_darbuotojai(char darbuotoju_failas[], int&kiekis, darbuotojas D[])
{
    ifstream fd(darbuotoju_failas);

    kiekis=0;
    while(!fd.eof())
    {
        fd>>D[kiekis].vardas;
        fd.get(D[kiekis].Pavarde, 25);
        fd>>D[kiekis].metai;
        kiekis++;
        fd.ignore();
    }

    fd.close();
}

void skaitymas_keitimai(char keitimu_failas[], int&k, darbuotojas K[])
{
    ifstream fd(keitimu_failas);

    fd>>k;
    for(int i=0; i<k; i++)
    {
        fd>>K[i].vardas;
        fd>>
    }

    fd.close();
}
