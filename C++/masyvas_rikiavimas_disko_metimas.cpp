#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    double P[100]; // Dalyvių masyvas
    int m,k; // Pirmos ir antros grupės dalyvių skaičius
    int a,n; // Kvalifikacinė normą, bendro masyvo dalyvių skaičius
    int i,j;
    ifstream fd("disko_metimas_data.txt");
    ofstream fr("disko_metimas_rez.txt");
    // Nuskaitymas į vieną masyvą
    fd>>m;
    for(i=0;i<m;i++) fd>>P[i];
    fd>>k;
    for(i=0;i<k;i++) fd>>P[i+m];

    fd>>a;
    n=m+k; // Bendro masyvo elementų kiekis
    // Bendro masyvo elementų rikiavimas mažėjimo tvarka
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if(P[j]>P[i]) swap(P[i],P[j]);

    for(i=0;i<12;i++) fr<<fixed<<setprecision(2)<<P[i]<<endl;
    fd.close();
    fr.close();
    return 0;
}
