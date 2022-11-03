#include <fstream>
using namespace std;

int main()
{
    int p,k,l; // Peržiūrų, puslapių ir lankytojų skaičius
    int P[999],L[999]; // Puslapiai ir lankytojai
    int sk; // Unikalus numeris
    int did; // Didžiausia reikšmė
    int i,j;
    ifstream fd("svetaine_data.txt");
    ofstream fr("svetaine_rez.txt");
    fd>>p>>k>>l;
    // Nuskaitymas
    for(i=0;i<p;i++) fd>>P[i]>>L[i];
    // Puslapio su daugiausia peržiūrų radimas
    for(i=1;i<=k;i++)
    {
        sk=0;
        for(j=0;j<p;j++)
            if(P[j]==i) sk++;

        if(i==1)did=sk;
        else if (sk>did) did=sk;
    }
    fr<<"Vienas puslapis daugiausia peržiūrėtas: "<<did;
    // Lankytojo, kuris peržiūrėjo daugiausia puslapių, radimas
    for(i=1;i<=l;i++)
    {
        sk=0;
        for(j=0;j<p;j++)
            if(L[j]==i) sk++;

        if(i==1)did=sk;
        else if (sk>did) did=sk;
    }
    fr<<"\nVienas lankytojas daugiausia peržiūrėjo: "<<did;

    fd.close();
    fr.close();
    return 0;
}
