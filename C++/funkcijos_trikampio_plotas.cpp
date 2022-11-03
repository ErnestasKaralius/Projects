#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;
double krastines_ilgis(int X[],int Y[],int i,int j);
double plotas(double k1,double k2,double k3);

int main()
{
    double k1,k2,k3; // Trikampio kraštinės
    int X[3],Y[3]; // Taško koordinatės
    ifstream fd("koordinates_trikampio_plotas_data.txt");
    ofstream fr("koordinates_trikampio_plotas_rez.txt");
    for(int i=0;i<3;i++) fd>>X[i]>>Y[i];

    k1=krastines_ilgis(X,Y,0,1);
    k2=krastines_ilgis(X,Y,1,2);
    k3=krastines_ilgis(X,Y,0,2);

    fr<<fixed<<setprecision(2)<<plotas(k1,k2,k3);

    fd.close();
    fr.close();
    return 0;
}

double krastines_ilgis(int X[],int Y[],int i,int j)
{
    double ilgis=(double)sqrt(pow(X[j]-X[i],2)+pow(Y[j]-Y[i],2));

    return ilgis;
}

double plotas(double k1,double k2,double k3)
{
    double p=(k1+k2+k3)/2; // Pusperimetris
    double s=sqrt(p*(p-k1)*(p-k2)*(p-k3));

    return s;
}


