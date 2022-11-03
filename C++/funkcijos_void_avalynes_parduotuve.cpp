#include <fstream>
#include <iomanip>
using namespace std;
void skaitymas(int&n,char L[],double K[]);
void kainu_suma(int n,char l,char L[],double K[],double&vsuma,double&msuma,double&vvid,double&mvid);
void rasymas(double vsuma,double msuma,double vvid,double mvid);

int main()
{
    int n;
    char L[100]; // Lyčių masyvas
    double K[100]; // Kainų masyvas

    double vsuma,msuma; // Vyriškų ir moteriškų batų kainos
    double vvid,mvid; // Vyriškų ir moteriškų batų vidurkis
    char l; // Lytis

    skaitymas(n,L,K);
    kainu_suma(n,'v',L,K,vsuma,msuma,vvid,mvid);
    kainu_suma(n,'m',L,K,vsuma,msuma,vvid,mvid);
    rasymas(vsuma,msuma,vvid,mvid);

    return 0;
}
// Duomenų skaitymas iš failo
void skaitymas(int&n,char L[],double K[])
{
    ifstream fd("avalynes_parduotuve_data.txt");
    fd>>n;
    for(int i=0;i<n;i++) fd>>L[i]>>K[i];
    fd.close();
}

// Vyriškų ir moteriškų batų sumos radimas bei kiek vidutiniškai kainavo viena pora
void kainu_suma(int n,char l,char L[],double K[],double&vsuma,double&msuma,double&vvid,double&mvid)
{
    double suma=0;
    int kiekis=0;
    for(int i=0;i<n;i++) if(L[i]==l) {suma=suma+K[i]; kiekis++;} // Sumuos tik nurodytos lyties batų kainas

    if(l=='v') {vsuma=suma; vvid=vsuma/kiekis;}
        else {msuma=suma; mvid=msuma/kiekis;}
}

// Kiek iš viso kainavo visos poros
double bendra_kaina(double vsuma,double msuma)
{
    double kaina=vsuma+msuma;

    return kaina;
}

void rasymas(double vsuma,double msuma,double vvid,double mvid)
{
    ofstream fr("avalynes_parduotuve_rez.txt");
    fr<<fixed<<setprecision(2)<<"Vyriška avalynė:\n";
    if(vsuma>0)
    {
        fr<<"Parduota: "<<vsuma<<endl;
        fr<<"Vidutiniškai kainavo: "<<vvid<<endl;
    }
    else fr<<"Prekiauta nebuvo\n";

    fr<<"Moteriška avalynė:\n";
    if(msuma>0)
    {
        fr<<"Parduota: "<<msuma<<endl;
        fr<<"Vidutiniškai kainavo: "<<mvid<<endl;
    }
    else fr<<"Prekiauta nebuvo\n";

    fr<<"\nBendra kaina: "<<bendra_kaina(vsuma,msuma);

    fr.close();
}

