#include <fstream>
using namespace std;

int main()
{
    int k1,k2; // 1kg ir 2kg miltai
    int p; // Pirkėjų skaičius
    int M[100]; // Norimų miltų kiekio masyvas
    int kiek1,kiek2; // Kiek pardavė 2kg miltų
    int suma1=0,suma2=0; // Kiek iš viso nupirkta 1kg ir 2 kg miltų pakelių
    int isigijo=0; // Kiek žmonių įsigijo bent 1kg miltų
    int gauta; // Kiek paskutinis žmogus, turintis bent 1kg miltų, gavo iš viso
    int i,j;
    ifstream fd("pakuotes_data.txt");
    ofstream fr("pakuotes_rez.txt");
    fd>>k1>>k2>>p;
    suma1=k1;suma2=k2;
    // Nuskaitymas
    for(i=0;i<p;i++) fd>>M[i];

    for(i=0;i<p;i++)
    {
        kiek1=kiek2=0;
        // Kiek liks 2kg miltų pakuočių
        for(j=0;j<M[i]/2&&k2!=0;j++) {k2=k2-1;kiek2=kiek2+2;}

        // Kiek liks 1kg miltų pakuočių
        for(j=0;j<M[i]-kiek2&&k1!=0;j++) {k1=k1-1;kiek1++;}

        // Kiek yra pirkėjų, kurie gavo bent viena miltų pakuotę ir kiek iš viso gavo
        if(kiek1>0||kiek2/2>0) {isigijo++;gauta=kiek1+kiek2;}
    }
    fr<<suma1-k1<<" "<<suma2-k2<<endl;
    fr<<isigijo<<endl;
    fr<<gauta;

    fd.close();
    fr.close();
    return 0;
}
