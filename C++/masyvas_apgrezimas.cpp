#include <fstream>
using namespace std;

int main()
{
    int sk, M[100]; // Skaičių kiekis, jų masyvas
    int tarp; // Tarpinis skaičius
    int i;
    ifstream fd("masyvo_aprezimas_data.txt");
    ofstream fr("masyvo_aprezimas_rez.txt");
    fd>>sk;

    // Nuskaitymas
    for(i=0;i<sk;i++) fd>>M[i];

    // Skaičių sukeitimas
    /*
    for(i=0;i<sk/2;i++)
    {
        tarp=M[i];
        M[i]=M[sk-1-i];
        M[sk-l]=tarp;
    }
    */
    for(i=0;i<sk/2;i++) swap(M[i],M[sk-1-i]);

    // Masyvo duomenų išvedimas
    for(i=0;i<sk;i++) fr<<M[i]<<endl;

    fd.close();
    fr.close();
    return 0;
}
