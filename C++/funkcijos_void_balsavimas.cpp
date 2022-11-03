#include <fstream>
#include <iomanip>
using namespace std;
void skaitymas(int&n,int&k, int B[], int K[]);
void rasymas(int n,int k, int B[],int K[]);

int main()
{
    int n,k; // Balsuojančių ir kandidatų skaičius
    int B[1000]; // Balsuojančių masyvas
    int K[100]; // Kandidatų masyvas

    skaitymas(n,k,B,K);
    rasymas(n,k,B,K);

    return 0;
}

void skaitymas(int&n,int&k, int B[],int K[])
{
    ifstream fd("geriausio_mokinio_balsavimas_data.txt");
    fd>>n>>k;
    for(int i=0;i<n;i++) fd>>B[i];
    for(int i=0;i<k;i++) K[i]=0;

    fd.close();
}

void rasymas(int n,int k, int B[],int K[])
{
    ofstream fr("geriausio_mokinio_balsavimas_rez.txt");
    for(int i=0;i<n;i++) K[B[i]-1]++;

    fr<<"Kandidato nr."<<setw(20)<<"Balsų skaičius\n";
    for(int i=0;i<k;i++) fr<<i+1<<setw(16)<<K[i]<<"\n";

    fr.close();
}
