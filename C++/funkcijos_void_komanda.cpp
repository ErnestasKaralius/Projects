#include <fstream>
#include <iomanip>
using namespace std;

void skaitymas(int&n, int&m, double N[], double M[]);
void rasymas(int n, int m, double N[], double M[]);

void kur_iterpti(int i, int&j, int n, double N[], double M[]);
void iterpimas(int i, int j, int n, double N[], double M[]);
void salinimas(int n, double N[]);


int main()
{
    int n,m;
    double N[20],M[10];

    skaitymas(n,m,N,M);
    rasymas(n,m,N,M);

    return 0;
}

void skaitymas(int&n, int&m, double N[], double M[])
{
    ifstream fd("suolininku_komanda_data_1.txt");
    fd>>n;
    for(int i=0;i<n;i++) fd>>N[i];
    fd.close();

    ifstream fe("suolininku_komanda_data_2.txt");
    fe>>m;
    for(int i=0;i<m;i++) fe>>M[i];
    fe.close();
}

void kur_iterpti(int i, int&j, int n, double N[], double M[])
{
    for(int e=0;e<n;e++)
    {
        if(M[i]>=N[e]&&M[i]<=N[e+1]) j=e+1;
        if(M[i]>N[n-1]) j=n;
        if(M[i]<N[0]) j=0;
    }
}

void iterpimas(int i, int j, int n, double N[], double M[])
{
    for(int e=n;e>j;e--) N[e]=N[e-1];
    N[j]=M[i];
}

void salinimas(int n, double N[])
{
    for(int i=0;i<n-1;i++) N[i]=N[i+1];
}

void rasymas(int n, int m, double N[], double M[])
{
    ofstream fr("suolininku_komanda_rez.txt");
    for(int i=0;i<m;i++)
    {
        int j;
        kur_iterpti(i,j,n,N,M);
        iterpimas(i,j,n,N,M);
        n++;
    }

    if(n<10) fr<<"Trūksta: "<<10-n<<"\n";
        else while(n>10) {salinimas(n,N); n--;}

    for(int i=0;i<n;i++) fr<<fixed<<setprecision(2)<<N[i]<<" ";
    fr.close();
}
