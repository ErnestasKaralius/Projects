#include <fstream>
using namespace std;
int perskaitys(int n,int a,int b);

int main()
{
    ifstream fd("knygos_skaitymas_data.txt");
    ofstream fr("knygos_skaitymas_rez.txt");
    int n; // Kiek iš viso perskaitė knygų
    int a,b; // Kiek perskaitė 1 d. ir kiek daugiau perskaitys kitas dienas
    fd>>n>>a>>b;
    fr<<perskaitys(n,a,b);

    fd.close();
    fr.close();
    return 0;
}

int perskaitys(int n,int a,int b)
{
    int suma=a;
    int dienos=1;
    while(suma<n)
    {
        a=a+b;
        suma=suma+a;
        dienos++;
    }

    return dienos;
}
