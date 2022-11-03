#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    char V[100][26]; // Vardų masyvas
    double A[100]; // Atsargų masyvas
    int n; // Dalyvių skaičius
    double g,s,k;
    int i,j;
    ifstream fd("char_misko_tyrimai_data.txt");
    ofstream fr("char_misko_tyrimai_rez.txt");
    fd>>n;
    fd.ignore();
    for(i=0;i<n;i++)
    {
        fd.get(V[i],25);
        fd>>g>>s>>k;
        A[i]=g+s+k; // Kiek iš viso atsargų
        fd.ignore();
    }
    // Rikiavimas mažėjimo tvarka
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if(A[i]<A[j]) {swap(V[i],V[j]); swap(A[i],A[j]);}

    for(i=0;i<n;i++) fr<<fixed<<setprecision(1)<<V[i]<<A[i]<<endl;



    fd.close();
    fr.close();
    return 0;
}
