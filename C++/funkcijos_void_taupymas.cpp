#include <fstream>
#include <iomanip>
using namespace std;
void skaitymas(int&k, double&a,double&b,double&c, double A[],double B[],double C[]);
void rasymas(int k, double a,double b,double c, double A[],double B[],double C[]);

double isleido_pinigu(int k,double P[]);
double islaidu_vidurkis(int k,double suma);
double liko_pinigu(double p,double suma);
int virsijo_kartu(int k,double A[],double B[],double C[]);

int main()
{
    int k; // Dienų skaičius
    double a,b,c; // Vaikinų turimi pinigai
    double A[100],B[100],C[100]; // Vaikinų išleisti pinigai

    skaitymas(k, a,b,c, A,B,C);
    rasymas(k, a,b,c, A,B,C);

    return 0;
}

void skaitymas(int&k, double&a,double&b,double&c, double A[],double B[],double C[])
{
    ifstream fd("taupymo_paskaita_data.txt");
    fd>>k;
    fd>>a>>b>>c;
    for(int i=0;i<k;i++) fd>>A[i]>>B[i]>>C[i];

    fd.close();
}

double isleido_pinigu(int k,double P[])
{
    double suma=0;
    for(int i=0;i<k;i++) suma=suma+P[i];

    return suma;
}

double islaidu_vidurkis(int k,double suma)
{
    double vid=suma/k;

    return vid;
}

double liko_pinigu(double p,double suma)
{
    double likutis=p-suma;

    return likutis;
}

int virsijo_kartu(int k,double A[],double B[],double C[])
{
    int kiekis=0;
    for(int i=0;i<k;i++)
    {
        if(A[i]>islaidu_vidurkis(k,isleido_pinigu(k,A))) kiekis++;
        if(B[i]>islaidu_vidurkis(k,isleido_pinigu(k,B))) kiekis++;
        if(C[i]>islaidu_vidurkis(k,isleido_pinigu(k,C))) kiekis++;
    }

    return kiekis;
}

void rasymas(int k, double a,double b,double c, double A[],double B[],double C[])
{
    double suma1=isleido_pinigu(k,A);
    double suma2=isleido_pinigu(k,B);
    double suma3=isleido_pinigu(k,C);
    ofstream fr("taupymo_paskaita_rez.txt");
    fr<<fixed<<setprecision(2)<<"Vaikinai išleido:\n"<<suma1<<" "<<suma2<<" "<<suma3;
    fr<<"\nDienos išlaidų vidurkis:\n"<<islaidu_vidurkis(k,suma1)<<" "<<islaidu_vidurkis(k,suma2)<<" "<<islaidu_vidurkis(k,suma3);
    fr<<"\nVaikinams liko pinigų:\n"<<liko_pinigu(a,suma1)<<" "<<liko_pinigu(b,suma2)<<" "<<liko_pinigu(c,suma3);
    fr<<"\nIšleido daugiau už savo dienos vidurkį kartų: "<<virsijo_kartu(k,A,B,C);

    fr.close();
}
