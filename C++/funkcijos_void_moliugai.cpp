#include <fstream>
#include <iomanip>
using namespace std;
void skaitymas(int&n,double&p1,double&p2,double S[]);
void tinkami_moliugai(int n,double p1,double p2,double S[],double T[],int&kiekis);
double moliugu_vidurkis(int n,double S[]);
void rasymas(double S[],double T[],int n,int kiekis);

int main()
{
    int n; // Moliūgų skaičius
    double p1,p2; // Svoriai
    double S[100]; // Visi moliūgai
    double T[100]; // Tinkami moliūgai
    int kiekis;

    skaitymas(n,p1,p2,S);
    tinkami_moliugai(n,p1,p2,S,T,kiekis);
    rasymas(S,T,n,kiekis);

    return 0;
}

void skaitymas(int&n,double&p1,double&p2,double S[])
{
    ifstream fd("ukininko_moliugai_data.txt");
    fd>>n;
    fd>>p1>>p2;
    for(int i=0;i<n;i++) fd>>S[i];

    fd.close();
}

void tinkami_moliugai(int n,double p1,double p2,double S[],double T[],int&kiekis)
{
    kiekis=0;
    for(int i=0;i<n;i++)
        if(S[i]>=p1&&S[i]<=p2)
        {
            T[kiekis]=S[i];
            kiekis++;
        }
}

double moliugu_vidurkis(int n,double S[])
{
    double suma=0;
    double vidurkis;
    for(int i=0;i<n;i++) suma=suma+S[i];

    vidurkis=suma/n;
    return vidurkis;
}

void rasymas(double S[],double T[],int n,int kiekis)
{
    ofstream fr("ukininko_moliugai_rez.txt");
    fr<<"Visų moliūgų vidutinis svoris: "<<fixed<<setprecision(3)<<moliugu_vidurkis(n,S);
    if(kiekis>0)
    {
        fr<<"\nĮ supirkimą atrinkta: "<<kiekis;
        fr<<"\nVidutinis vieno atrinkto moliūgo svoris: "<<moliugu_vidurkis(kiekis,T);
        fr<<"\nAtrinktų moliūgų svorių sąrašas: "; for(int i=0;i<kiekis;i++) fr<<T[i]<<" ";
    }
    else fr<<"\nNebuvo atrinkta";

    fr.close();
}
