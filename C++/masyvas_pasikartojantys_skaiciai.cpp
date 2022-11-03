#include <fstream>
using namespace std;

int main()
{
    int M[100]; // Skaičių masyvas
    int n,i,j; // Skaičių kiekis
    ifstream fd("pasikartojantys_skaiciai_data.txt");
    ofstream fr("pasikartojantys_skaiciai_rez.txt");
    fd>>n;
    // Nuskaitymas
    for(i=0;i<n;i++) fd>>M[i];

    // Dviejų vienodų skaičių masyve radimas
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if(M[i]==M[j]) fr<<i+1<<" "<<j+1<<" "<<M[i];

    fd.close();
    fr.close();
    return 0;
}
