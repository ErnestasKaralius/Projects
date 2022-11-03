#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int n,i,suma=0;      // Namai gatvėje
    int gk=0,gd=0,nd=0;  // Gyventojai kairėje, gyventojai dešinėje, namai dešinėje
    int N[499], G[499];  // Namai, gyventojai
    ifstream fd("gyventojai_data.txt");
    ofstream fr("gyventojai_rez.txt");
    fd>>n;
    // Nuskaitymas
    for(i=0;i<n;i++) fd>>N[i]>>G[i];
    // Gyventojų skaičius
    for(i=0;i<n;i++) suma=suma+G[i];
    // Kiek gyvena kairėje ir dešinėje
    for (i=0;i<n;i++)
    {
        if(N[i]%2==0) {nd++;gd=gd+G[i];}
            else gk=gk+G[i];
    }
    fr<<"Gyventojų skaičius: "<<suma<<endl;
    fr<<"Gyvena kairėje pusėje: "<<gk<<endl;
    fr<<"Gyvena dešinėje pusėje: "<<gd<<endl;
    fr<<fixed<<setprecision(2)<<"Vidutiniškai gyventojų kairiuosiuose namuose: "<<(double)gk/(n-nd)<<endl;
    fr<<"Vidutiniškai gyventojų dešiniuosiuose namuose: "<<(double)gd/nd;

    fd.close();
    fr.close();
    return 0;
}
