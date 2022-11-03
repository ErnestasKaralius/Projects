#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int N[29];
    int n,i,suma=0; // Mokinių skaičius
    ifstream fd("skaitytojai_data.txt");
    ofstream fr("skaitytojai_rez.txt");
    fd>>n;
    // Nuskaitymas
    for(i=0;i<n;i++)fd>>N[i];
    // Suma
    for(i=0;i<n;i++)suma=suma+N[i];

    fr<<"Perskaitė knygų: "<<suma<<endl;
    fr<<fixed<<setprecision(0)<<"Vidutiniškai mokinys per 10 mėnesių perskaitė: "<<(double)suma/n<<endl;
    fr<<fixed<<setprecision(1)<<"Vidutiniškai mokinys per mėnesį perskaitė: "<<(double)suma/n/10;

    fd.close();
    fr.close();
    return 0;
}
