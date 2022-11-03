#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int n,k; // Balsavusių ir kandidatų skaičiai
    int B[100]; // Balsų kiekio masyvas
    int sk;
    int i;
    ifstream fd("balsavimai_data.txt");
    ofstream fr("balsavimai_rez.txt");
    fd>>n>>k;
    // Masyvo nulinimas
    for(i=0;i<k;i++) B[i]=0;
    // Kiek kartų balsavo už kandidatą
    for(i=0;i<n;i++)
    {
        fd>>sk;
        B[sk-1]++;
    }
    fr<<"Kanditado nr."<<setw(21)<<"Balsų kiekis\n";
    for(i=0;i<k;i++)
        fr<<i+1<<setw(20)<<B[i]<<endl;

    fd.close();
    fr.close();
    return 0;
}
