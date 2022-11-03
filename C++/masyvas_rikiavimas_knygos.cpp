#include <fstream>
using namespace std;

int main()
{
    int K[20],B[20]; // Knygų kodų ir balų masyvai
    int n,m; // Knygų ir vertintojų skaičius
    int sk; // Balas
    int did,maz; // Didžiausi ir mažiausi skaičiai
    int i,j;
    ifstream fd("skaitomiausios_knygos_data.txt");
    ofstream fr("skaitomiausios_knygos_rez.txt");
    fd>>n>>m;
    // Duomenų įdėjimas į 2 masyvus
    for(i=0;i<n;i++)
    {
        fd>>K[i]; // Balo įdėjimas į masyvą
        for(j=1;j<=m;j++) // Didžiausio ir mažiausio balo radimas
        {
            fd>>sk;
            if(j==1) {did=sk; maz=sk;}
            if(sk>did) did=sk;
            if(sk<maz) maz=sk;
        }
        B[i]=did+maz; // Galutinio įvertinimo įdėjimas į masyvą
    }

    // Rikiavimas didėjimo tvarka
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if(K[i]>K[j]) {swap(K[i],K[j]); swap(B[i],B[j]);}

    fr<<"Knygų įvertinimai:\n";
    for(i=0;i<n;i++) fr<<K[i]<<" "<<B[i]<<endl;

    // Geriausio ir blogiausio įvertinimo radimas
    for(i=0;i<n;i++)
    {
        if(i==0) {did=B[i];maz=B[i];}
        if(B[i]>did) did=B[i];
        if(B[i]<maz) maz=B[i];
    }
    fr<<"Blogiausiai įvertintos knygos: ";
    for(i=0;i<n;i++) if(B[i]==maz) fr<<K[i]<<" ";

    fr<<"\nGeriausiai įvertintos knygos: ";
    for(i=n-1;i>-1;i--) if(B[i]==did) fr<<K[i]<<" ";

    fd.close();
    fr.close();
    return 0;
}
