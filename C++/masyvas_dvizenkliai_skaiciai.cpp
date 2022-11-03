#include <fstream>
using namespace std;

int main()
{
    int S[100],i; // Sveikųjų skaičių masyvas
    int sk; // Sveikųjų skaičių kiekis
    int kiekis=0;
    ifstream fd("dvizenkliai_skaiciai_data.txt");
    ofstream fr("dvizenkliai_skaiciai_rez.txt");
    fd>>sk;
    // Nuskaitymas
    for(i=0;i<sk;i++) fd>>S[i];

    // Dviženklių skaičių, kurių pirmasis skaitmuo yra 3, kiekio radimas
    for(i=0;i<sk;i++)
        if(S[i]/10==3) kiekis++;

    fr<<kiekis;

    fd.close();
    fr.close();
    return 0;
}
