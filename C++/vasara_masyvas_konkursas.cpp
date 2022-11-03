#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int n,m; // Sportininkų skaičius
    double M[20]; // Geriausių rezultatų masyvas
    int i,j;
    ifstream fd("suolininku_komanda_data_1.txt");
    ifstream fe("suolininku_komanda_data_2.txt");
    ofstream fr("suolininku_komanda_rez.txt");
    // Nuskaitymas iš dviejų failų
    fd>>n;
    for(i=0;i<n;i++) fd>>M[i];
    fe>>m;
    n=n+m;
    for(i;i<n;i++) fe>>M[i];

    // Rikiavimas didėjimo tvarka
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if(M[i]>M[j])swap(M[i],M[j]);


    if(n<10){ fr<<"Trūksta: "<<10-n<<endl;i=0;}
        else i=n-10;

    fr<<"Atrinktų sportininkų rezultatų sąrašas:\n";
        for(i;i<n;i++) fr<<fixed<<setprecision(2)<<M[i]<<" ";

    fd.close();
    fe.close();
    fr.close();
    return 0;
}
