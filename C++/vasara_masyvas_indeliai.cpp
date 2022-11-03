#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int n; // Klientų skaičius
    double M[10000]; // Indėliai
    int K[10000]; // Kodai
    double did,maz; // Didžiausias ir mažiausias indėlis
    double suma=0; // Indėlių suma
    int dk=1,mk=1; // Didžiausio ir mažiausio indėlio kodas
    int i,j;
    ifstream fd("indeliai_data.txt");
    ofstream fr("indeliai_rez.txt");
    fd>>n;
    // Nuskaitymas
    for(i=0;i<n;i++) {fd>>M[i];K[i]=i+1;}

    // Didžiausio, mažiausio indėlio ir jų kodų radimas
    for(i=0;i<n;i++)
    {
        suma=suma+M[i];
        if(i==0) {did=M[i];maz=M[i];}
        if(M[i]>did) {did=M[i];dk=K[i];}
        if(M[i]<maz) {maz=M[i];mk=K[i];}
    }
    fr<<fixed<<setprecision(2)<<"Didžiausias indėlis: "<<did<<", kodas: "<<dk;
    fr<<"\nMažiausias indėlis: "<<maz<<", kodas: "<<mk;
    fr<<"\nVidutinis indėlio dydis: "<<suma/n<<endl;

   // Indėlių ir kodų rikiavimas
   for(i=0;i<n-1;i++)
     for(j=i+1;j<n;j++)
        if(M[i]<M[j]) {swap(M[i],M[j]);swap(K[i],K[j]);}

    // Išrikiuotų indėlių išvedimas
    fr<<"\nKodas"<<setw(20)<<"Indėlis\n";
    for(i=0;i<n;i++) fr<<K[i]<<" "<<setw(24)<<M[i]<<endl;

    fd.close();
    fr.close();
    return 0;
}
