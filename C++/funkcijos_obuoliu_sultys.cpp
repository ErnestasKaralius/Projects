#include <fstream>
using namespace std;
int penki_litrai(int i,int S[]);
int du_litrai(int i,int S[]);

int main()
{
    int S[100]; // Sulčių kiekis
    int n; // Ūkininkų skaičius
    ifstream fd("obuoliu_sultys_data.txt");
    ofstream fr("obuoliu_sultys_rez.txt");
    fd>>n;
    // Nuskaitymas
    for(int i=0;i<n;i++) fd>>S[i];

    for(int i=0;i<n;i++)
    {
        fr<<penki_litrai(i,S)<<" ";
        S[i]=S[i]%5;

        fr<<du_litrai(i,S)<<" ";
        S[i]=S[i]%2;

        fr<<S[i]<<endl;
    }

    fd.close();
    fr.close();
    return 0;
}

int penki_litrai(int i,int S[])
{
    int uzpilde=S[i]/5;
    return uzpilde;
}

int du_litrai(int i,int S[])
{
    int uzpilde=S[i]/2;
    return uzpilde;
}

