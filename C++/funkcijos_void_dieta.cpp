#include <fstream>
using namespace std;
void kiek_suvartojo(int i,int G[],double a,double b,double r,double&akiekis,double&bkiekis,double&rkiekis);
int dienu_skaicius(int G[],int n);

int main()
{
    int n; // Dienų skaičius
    double a,b,r; // Angliavandenių, baltymų, riebalų 100g
    double akiekis,bkiekis,rkiekis; // Angliavandenių, baltymų, riebalų kiekis
    int G[100]; // Kiekvienos dienos gramų kiekis
    ifstream fd("grikiu_dieta_data.txt");
    ofstream fr("grikiu_dieta_rez.txt");
    fd>>n;
    fd>>a>>b>>r;
    for(int i=0;i<n;i++)
    {
        fd>>G[i];
        kiek_suvartojo(i,G,a,b,r,akiekis,bkiekis,rkiekis);
        fr<<akiekis<<" "<<bkiekis<<" "<<rkiekis<<endl;
    }
    fr<<dienu_skaicius(G,n);


    fd.close();
    fr.close();
    return 0;
}

void kiek_suvartojo(int i,int G[],double a,double b,double r,double&akiekis,double&bkiekis,double&rkiekis)
{
    akiekis=a*G[i]/100;
    bkiekis=b*G[i]/100;
    rkiekis=r*G[i]/100;
}

int dienu_skaicius(int G[],int n)
{
    int kiekis=0;
    for(int i=0;i<n;i++) if((double)G[i]/100*349>=1800) kiekis++;

    return kiekis;
}
