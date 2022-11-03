#include <fstream>
using namespace std;

int main()
{
    int U[100]; // Ūgių masyvas
    int n,m; // Ūgių skaičius
    int sk;
    int did,vieta;
    int i,j;
    ifstream fd("zalgirio_komanda_senbuviai.txt");
    ifstream fe("zalgirio_komanda_naujokai.txt");
    ofstream fr("zalgirio_komanda_rez.txt");
    fd>>n;
    // Senbuvių nuskaitymas
    for(i=0;i<n;i++) fd>>U[i];

    // Skaičiaus įterpimas į senbuvių masyvą
    fe>>m;
    for(i=0;i<m;i++)
    {
        fe>>sk;
        for(j=0;j<n;j++)
        {
            // Ar didesnis už pradinį ir dabartinį skaičių
            if(sk>=U[j]&&sk<=U[j-1]) vieta=j;
                // Ar mažesnis už paskutinį masyvo skaičių
                else if(U[n-1]>=sk) vieta=j+1;
        }
        // Įterpimas
        for(j=n;j>vieta;j--) U[j]=U[j-1];
        U[vieta]=sk;
        n++;

    }
    for(i=0;i<n;i++) fr<<U[i]<<" ";

    fd.close();
    fe.close();
    fr.close();
    return 0;
}
