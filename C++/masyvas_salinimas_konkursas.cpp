#include <fstream>
using namespace std;

int main()
{
    int n,i; // Dalyvių skaičius
    int K[100]; // Balų masyvas
    int suma=0; // Balų suma
    double vid; // Balų vidurkis
    ifstream fd("salinimas_konkursas_data.txt");
    ofstream fr("salinimas_konkursas_rez.txt");
    fd>>n;
    //Nuskaitymas
    for(i=0;i<n;i++) fd>>K[i];

    // Balų vidurkio skaičiavimas
    for(i=0;i<n;i++) suma=suma+K[i];
    vid=(double)suma/n;

    // Mokinių, kurių balas mažesnis už vidurkį, šalinimas
    for(i=0;i<n;i++)
        if(K[i]<vid)
        {
            K[i]=K[n-1];
            n--;
            i--;
        }

    for(i=0;i<n;i++) fr<<K[i]<<" ";

    fd.close();
    fr.close();
    return 0;
}
