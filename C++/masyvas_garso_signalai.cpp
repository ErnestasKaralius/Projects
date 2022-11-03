#include <fstream>
using namespace std;

int main()
{
    int K[47]; // Eilę sudarantys sveikieji skaičiai
    int n,k; // Eilių skaičius ir sveikųjų skaičių kiekis eilėje
    int sk,ask; // Skaičius ir ankstesnis skaičius
    int i,j;
    ifstream fd("garso_signalai_data.txt");
    ofstream fr("garso_signalai_rez.txt");
    fd>>n>>k;
    for(i=1;i<=n;i++)
    {
        // Nuskaitymas
        for(j=0;j<k;j++) fd>>K[j];
        // Skaičiavimai su masyvu
        for(j=0;j<k;j++)
        {
            sk=K[j];
            if(j==0) // Pirmasis eilės skaičius
            {
                j=1;
                sk=(sk+K[j])/2;
                j=0;
            }
            else if(j==k-1) sk=(ask+sk)/2; // Paskutinysis eilės skaičius

            else // Kiti skaičiai
            {
                j++;
                sk=(ask+sk+K[j])/3;
                j--;
            }
            ask=K[j];
            fr<<sk<<" ";
        }
        fr<<"\n";
    }
    fd.close();
    fr.close();
    return 0;
}
