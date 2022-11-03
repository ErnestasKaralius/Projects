#include <fstream>
using namespace std;

void skaitymas(int&k, int Skaicius[], int Korteles[]);
void rasymas(int k, int Skaicius[], int Korteles[]);

int korteliu_skaicius(int sk, int k, int Korteles[]);
int korteliu_suma(int sk, int k, int Skaicius[], int Korteles[]);

int main()
{
    int k;
    int Korteles[100],Skaicius[100];

    skaitymas(k,Skaicius,Korteles);
    rasymas(k,Skaicius,Korteles);

    return 0;
}

void skaitymas(int&k, int Skaicius[], int Korteles[])
{
    ifstream fd("korteles_data.txt");
    fd>>k;
    for(int i=0; i<k; i++) fd>>Skaicius[i]>>Korteles[i];

    fd.close();
}

int korteliu_skaicius(int sk, int k, int Korteles[])
{
    int suma=0;
    for(int i=0; i<k; i++)
        if(Korteles[i]%2 == sk) suma+=Korteles[i];

    return suma;
}

int korteliu_suma(int sk, int k, int Skaicius[], int Korteles[])
{
    int suma=0;
    for(int i=0; i<k; i++)
        if(Korteles[i]%2 == sk) suma+=Korteles[i]*Skaicius[i];

    return suma;
}

void rasymas(int k, int Skaicius[], int Korteles[])
{
    ofstream fr("korteles_rez.txt");

    fr<<korteliu_skaicius(0,k,Korteles)<<" "<<korteliu_suma(0,k,Skaicius,Korteles)<<endl;
    fr<<korteliu_skaicius(1,k,Korteles)<<" "<<korteliu_suma(1,k,Skaicius,Korteles);

    fr.close();
}
