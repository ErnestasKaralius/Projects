#include <fstream>
using namespace std;

int main()
{
    int M[365]; // Slėgio duomenų masyvas
    int sk,i; // Parų skaičius
    int kiekis=0;
    ifstream fd("atmosferos_slegis_data.txt");
    ofstream fr("atmosferos_slegis_rez.txt");
    fd>>sk;
    // Nuskaitymas
    for(i=0;i<sk;i++) fd>>M[i];

    // Parų, kurių slėgis buvo didesnis už p1 ir mažesnis už p2, skaičius
    for(i=0;i<sk;i++)
        if(M[i]>M[1]&&M[i]<M[2]) kiekis++;

    fr<<kiekis;

    fd.close();
    fr.close();
    return 0;
}
