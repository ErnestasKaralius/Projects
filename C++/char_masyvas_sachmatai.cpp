#include <fstream>
using namespace std;

int main()
{
    char F[1000]; // Figūros
    char T[6] = {'p','b','z','r','v','k'}; // Tipai
    int S[6] = {0,0,0,0,0,0}; // Kiekvieno tipo kiekis
    int K[6] = {16,4,4,4,2,2}; // Komplektui reikalingos figūros
    int n; // Figūrų skaičius
    int kiekis=0; // Komplektų kiekis
    int i,j;
    bool vietos=1;
    ifstream fd("sachmatai_data.txt");
    ofstream fr("sachmatai_rez.txt");
    fd>>n;
    // Figūrų raidžių nuskaitymas į simbolių masyvą
    for(i=0;i<n;i++) fd>>F[i];

    // Kiekvienos rūšies kiekio radimas
    for(i=0;i<6;i++)
    {
        for(j=0;j<n;j++) if(F[j]==T[i]) S[i]++;
        fr<<T[i]<<" "<<S[i]<<endl;
    }
    // Komplektų kiekio radimas
    while(vietos)
    {
        for(i=0;i<6;i++) if(S[i]<K[i]) vietos=0; // Ar galima sudaryti komplektą
        if(vietos==1) // Jei galima, jį sudarome
        {
            for(i=0;i<6;i++) S[i]=S[i]-K[i];
            kiekis++; // Padidiname komplektų kiekį 1
        }
    }
    fr<<kiekis<<endl;
    for(i=0;i<6;i++) fr<<T[i]<<" "<<S[i]<<endl;

    fd.close();
    fr.close();
    return 0;
}
