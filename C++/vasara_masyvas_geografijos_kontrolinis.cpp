#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int p; // Pažymių kiekis
    int R[10]; // Kiekvieno pažymio kiekio masyvas
    int sk; // Pažymys
    int i;
    ifstream fd("geografija_data.txt");
    ofstream fr("geografija_rez.txt");
    fd>>p;
    // Masyvo nulinimas
    for(i=0;i<10;i++) R[i]=0;

    // Kiekvieno pažymio kieko radimas
    for(i=0;i<p;i++)
    {
        fd>>sk;
        R[sk-1]=R[sk-1]++;
    }

    // Vieno pažymio vertė procentais
    double vid=(double)100/p;

    // Procentų skaičiavimas
    for(i=0;i<10;i++) fr<<fixed<<setprecision(2)<<i+1<<" "<<R[i]*vid<<endl;

    fd.close();
    fr.close();
    return 0;
}
