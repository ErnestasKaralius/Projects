#include <fstream>
using namespace std;

int main()
{
    int sk,i; // Gėlių rūšių skaičius
    int M[30]; // Gėlių masyvas
    int did; // Ilgiausias laikas, kai gėlė nenuvys
    ifstream fd("geliu_puokste_data.txt");
    ofstream fr("geliu_puokste_rez.txt");
    fd>>sk;

    // Nuskaitymas
    for(i=0;i<sk;i++) fd>>M[i];

    // Ilgiausiai žydinčios gėlės radimas
    did=M[0];
    for(i=1;i<sk;i++) if(M[i]>did) did=M[i];
    fr<<"Visos gėlės nuvys po "<<did<<" d.\n";

    // Gėlių numerių radimas, kurias galima išlaikyti ilgiausiai
    fr<<"Gėlių, kurias reiktų dėti į puokštę, numeriai:\n";
    for(i=0;i<sk;i++) if(M[i]==did) fr<<i+1<<" ";

    fd.close();
    fr.close();
    return 0;
}
