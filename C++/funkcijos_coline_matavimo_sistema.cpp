#include <fstream>
#include <iomanip>
using namespace std;
double coliai(int i);
double pedos(int i,double C[]);
double jardai(int i,double P[]);

int main()
{
    double C[5],P[5],J[5];
    ofstream fr("coliai_matavimai_rez.txt");

    for(int i=0;i<5;i++)
    {
        C[i]=coliai(i+1);
        P[i]=pedos(i,C);
        J[i]=jardai(i,P);
        fr<<fixed<<setprecision(2)<<C[i]<<" "<<P[i]<<" "<<J[i]<<endl;
    }

    fr.close();
    return 0;
}

double coliai(int i)
{
    double c=i*100/2.54;

    return c;
}

double pedos(int i,double C[])
{
    double p=C[i]/12;

    return p;
}

double jardai(int i,double P[])
{
    double j=P[i]/3;

    return j;
}
