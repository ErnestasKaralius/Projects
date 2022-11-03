#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int N[29]; // Didžiausias mokinių skaičius
    int n,i; // Mokiniai
    int bsk=0,bsum=0,msum=0; // Vaikinų skaičius ir vaikinų bei merginų ūgių sumos
    int bkom=0,mkom=0; // Vaikinų ir merginų komandos narių skaičius
    ifstream fd("ugiai_data.txt");
    ofstream fr("ugiai_rez.txt");
    fd>>n;
    // Nuskaitymas
    for(i=0;i<n;i++) fd>>N[i];
    // Vaikinų ir merginų skaičius, jų ūgių sumos skaičiavimas
    for(i=0;i<n;i++)
    {
        if(N[i]<0)
        {
            bsk++;
            bsum=bsum+N[i]*-1;
            if(N[i]>=175)bkom++;
        }
        else
        {
            msum=msum+N[i];
            if(N[i]>=175)mkom++;
        }
    }
    fr<<fixed<<setprecision(1)<<"Visų mokinių ūgių vidurkis: "<<(double)(bsum+msum)/n<<endl;
    fr<<fixed<<setprecision(2)<<"Merginų ūgių vidurkis: "<<(double)msum/(n-bsk)<<endl;
    fr<<"Vaikinų ūgių vidurkis: "<<(double)bsum/bsk;

    if(bkom>=7)fr<<"\n\nVaikinų komandos sudaryti galima\n";
        else fr<<"\n\nVaikinų komandos sudaryti negalima\n";

    if(mkom>=7)fr<<"Merginų komandos sudaryti galima";
        else fr<<"Merginų komandos sudaryti negalima";

    fd.close();
    fr.close();
    return 0;
}
