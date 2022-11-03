#include <fstream>
using namespace std;

void skaitymas(int&n, int Ilipo[], int Islipo[]);
void rasymas(int n, int Ilipo[], int Islipo[]);

int main()
{
    int n;
    int Ilipo[101], Islipo[101];

    skaitymas(n,Ilipo,Islipo);
    rasymas(n,Ilipo,Islipo);

    return 0;
}

void skaitymas(int&n, int Ilipo[], int Islipo[])
{
    ifstream fd("tyrimai_data.txt");

    int sk,k;
    for(int i=1; i<=n; i++)
    {
        Ilipo[i]=0;
        Islipo[i]=0;
    }

    fd>>n;
    for(int i=1; i<=n; i++)
    {
        fd>>sk>>k;
        if(k > 0)
            Ilipo[sk] += k;
        else
            Islipo[sk] -= k;
    }

    fd.close();
}

void rasymas(int n, int Ilipo[], int Islipo[])
{
    ofstream fr("tyrimai_rez.txt");

    for(int i=1; i<=n; i++)
        if(Ilipo[i] > 0)
            fr<<i<<"      ";

    fr<<"\n";
    for(int i=1; i<=n; i++)
        if(Ilipo[i] > 0)
            fr<<Ilipo[i]<<"      ";

    fr<<"\n";
    for(int i=1; i<=n; i++)
        if(Islipo[i] <= 0)
            fr<<Islipo[i]<<"      ";



    fr.close();
}
