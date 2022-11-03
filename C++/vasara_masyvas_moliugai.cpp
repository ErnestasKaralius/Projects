#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int n; // Užaugintų moliūgų skaičius
    double p1, p2; // Svorio ribos
    double M[99]; // Moliūgų masyvas
    double svoris=0,asvoris; // Visų moliūgų svoris bei atrinktų
    int sk=0; // Atrinktų moliūgų skaičius
    int i,j;
    ifstream fd("moliugai_data.txt");
    ofstream fr("moliugai_rez.txt");
    fd>>n>>p1>>p2;
    // Nuskaitymas
    for(i=0;i<n;i++) fd>>M[i];
    // Visų moliūgų svorio skaičiavimas
    for(i=0;i<n;i++) svoris=svoris+M[i];

    fr<<fixed<<setprecision(3)<<"Vidutinis svoris: "<<svoris/n<<" kg"<<endl;
    asvoris=svoris;
    for(i=0;i<n;i++)
    {
        if(M[i]>=p1&&M[i]<=p2) sk++;
            else
            {
                // Atrinktų moliūgų svorio skaičiavimas
                asvoris=asvoris-M[i];
                // Neatrinktų moliūgų įdėjimas į masyvo galą
                for(j=i;j<n-1;j++) M[j]=M[j+1];
                n--;
                i--;
            }
    }
    if(sk==0) fr<<"Atrinktų moliūgų nėra";
        else
        {
            fr<<"Atrinkta: "<<sk<<endl;
            fr<<"Vidutinis atrinkto svoris: "<<asvoris/sk<<" kg"<<endl;
            fr<<"Atrinktų moliūgų svorių sąrašas: ";
                for(i=0;i<n;i++) fr<<M[i]<<" ";
        }

    fr.close();
    fd.close();
    return 0;
}
