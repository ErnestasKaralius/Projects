#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    int G[100]; // Konteinerio talpos masyvas
    int n,g; // Kiekvieno gamintojo gaminių skaičius, konteinerio talpa
    int p,suma=0; // Produktai, suma
    int l,i; // Likutis
    ifstream fd("konteineriai_data.txt");
    ofstream fr("konteineriai_rez.txt");
    fd>>n>>g;
    // Masyvo reikšmių prilyginimas nuliui
    for(i=0;i<g;i++) G[i]=0;

    // Konteinerių skaičius, likutis
    for(i=1;i<=n;i++)
    {
        fd>>p;
        G[0]=G[0]+p/g;
        l=p%g;
        if(l!=0)G[l]++;
    }

    // Sumos skaičiavimas
    for(i=0;i<g;i++) suma=suma+G[i];
    fr<<suma<<endl;
    fr<<G[0]<<endl;
    // Nepilnų konteinerių skaičius
    for(i=g-1;i>0;i--) fr<<G[i]<<" "<<i<<endl;

    fd.close();
    fr.close();
    return 0;
}
