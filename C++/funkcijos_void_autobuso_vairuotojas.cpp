#include <fstream>
using namespace std;
void skaitymas(int A[],int&s,int&a);
void rasymas(int A[],int s,int a);

double kilometru_vidurkis(int A[]);
int dienu_kiekis(int A[], int s,int j);
int labiausiai_pazeidziama(int A[],int s);
int galutinis_atlyginimas(int A[], int s,int a);

int main()
{
    int A[20]; // Nuvažiuotas atstumas
    int s, a; // Kiek reikia nuvažiuoti ir atlyginimas

    skaitymas(A,s,a);
    rasymas(A,s,a);

    return 0;
}

void skaitymas(int A[],int&s,int&a)
{
    ifstream fd("autobuso_vairuotojo_rezimas_data.txt");
    fd>>s>>a;
    for(int i=0;i<20;i++) fd>>A[i];

    fd.close();
}

double kilometru_vidurkis(int A[])
{
    int suma=0;
    for(int i=0;i<20;i++) suma=suma+A[i];

    double vidurkis=(double)suma/20;

    return vidurkis;
}

int dienu_kiekis(int A[], int s,int j)
{
    int kiekis=0;
    if(j==1) for(int i=0;i<20;i++) if(A[i]>s) kiekis++;
    if(j==2) for(int i=0;i<20;i++) if(A[i]<s) kiekis++;
    if(j==3) for(int i=0;i<20;i++) if(A[i]>s*1.2||A[i]<s*0.8) kiekis++;

    return kiekis;
}

int labiausiai_pazeidziama(int A[],int s)
{
    int did=0,vieta;
    int skirtumas;
    for(int i=0;i<20;i++)
    {
        if(A[i]>s*1.2) skirtumas=A[i]-s*1.2;
            else if(A[i]<s*0.8) skirtumas=s*0.8-A[i];

        if(skirtumas>did) {did=skirtumas;vieta=i+1;}
    }

    return vieta;
}

int galutinis_atlyginimas(int A[], int s,int a)
{
    int skirtumas;
    for(int i=0;i<20;i++)
        if(A[i]>s*1.2) {skirtumas=A[i]-s*1.2; a=a-skirtumas;}
            else if(A[i]<s*0.8) {skirtumas=s*0.8-A[i]; a=a-skirtumas;}

    return a;
}

void rasymas(int A[],int s,int a)
{
    ofstream fr("autobuso_vairuotojo_rezimas_rez.txt");

    fr<<"Vidurkis: "<<kilometru_vidurkis(A);
    fr<<"\nViršijo dienų: "<<dienu_kiekis(A,s,1);
    fr<<"\nAtsiliko dienų: "<<dienu_kiekis(A,s,2);
    fr<<"\nPažeidė dienų: "<<dienu_kiekis(A,s,3);
    fr<<"\nLabiausiai pažeidė dieną: "<<labiausiai_pazeidziama(A,s);
    fr<<"\nGalutinis atlyginimas: "<<galutinis_atlyginimas(A,s,a);

    fr.close();
}


