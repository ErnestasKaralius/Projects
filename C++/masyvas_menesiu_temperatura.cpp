#include <fstream>
using namespace std;

int main()
{
    int t,i; // Parų skaičius
    double T[31]; // Temperatūros masyvas (vienas mėnuo)
    int kiekis=0;
    ifstream fd("menesiu_temperatura_data.txt");
    ofstream fr("menesiu_temperatura_rez.txt");
    fd>>t;
    // Nuskaitymas
    for(i=0;i<t;i++) fd>>T[i];

    // Teigiamų temperatūrų, ne didesniu už T0, kiekio radimas
    for(i=0;i<t;i++)
        if(T[i]>0&&T[i]<=T[0]) kiekis++;

    fr<<kiekis;

    fd.close();
    fr.close();
    return 0;
}
