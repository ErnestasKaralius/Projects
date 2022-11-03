#include <fstream>
using namespace std;

int main()
{
    int S[499],V[499]; // Siuntų ir veržlų masyvas
    int n; // Siuntų skaičius
    int suma; // Veržlių suma
    int did,rusis; // Didžiausia suma ir jos veržlės rūšis
    int i,j;
    ifstream fd("remonto_dirbtuves_data.txt");
    ofstream fr("remonto_dirbtuves_rez.txt");
    fd>>n;
    // Nuskaitymas į 2 masyvus
    for(i=0;i<n;i++) fd>>S[i]>>V[i];

    // Kiekvienos rūšies veržlių kiekio radimas
    for(i=0;i<n;i++)
    {
        suma=V[i];
        for(j=i+1;j<n;j++)
            if(S[i]==S[j])
            {
                suma=suma+V[j];
                S[j]=S[n-1]; V[j]=V[n-1]; // Pasikartojančias rūšis įdedame į masyvo galą
                n--; // Jį sumažiname
                j--; // Dar kartą tikriname rūšį
            }
        fr<<S[i]<<" "<<suma<<endl;

        if(i==0) {rusis=S[i];did=suma;}
        if(suma>did) {rusis=S[i];did=suma;}
    }
    fr<<"Daugiausia veržlių gauta iš "<<rusis<<" rūšies";

    fd.close();
    fr.close();
    return 0;
}
