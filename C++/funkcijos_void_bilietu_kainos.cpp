#include <fstream>
#include <iomanip>
using namespace std;
void kainos(int B[],int eiles,double&suma,double&vidurkis);

int main()
{
    int B[100];
    int eiles,vietos;
    int sk;
    ifstream fd("bilietu_kainos_data.txt");
    ofstream fr("bilietu_kainos_rez.txt");
    fd>>eiles>>vietos;
    for(int i=0;i<eiles;i++)
    {
        int kiekis=0;
        for(int j=0;j<vietos;j++) {fd>>sk; kiekis=kiekis+sk;}
        B[i]=kiekis;
    }
    double suma=0,vidurkis;
    kainos(B,eiles,suma,vidurkis);
    fr<<suma<<" "<<fixed<<setprecision(2)<<vidurkis;

    fd.close();
    fr.close();
    return 0;
}

void kainos(int B[],int eiles,double&suma,double&vidurkis)
{
    int kiekis=0;
    for(int i=0;i<eiles;i++)
    {
        kiekis=kiekis+B[i];
        if(i>=4) suma=suma+B[i]*40;
        else if(i==3||i==2) suma=suma+B[i]*70;
            else suma=suma+B[i]*100;
    }
    vidurkis=suma/kiekis;
}





