#include <fstream>
#include <string>
using namespace std;

void rikiuoti(int n, int m, string Vardai[], int Minutes[], int Sekundes[]);
void rasyti(int n, string Vardai[], int Minutes[], int Sekundes[]);

int main()
{
    int n,m;

    string Vardai[30];
    int Valandos[30], Minutes[30], Sekundes[30];

    string Finisuotojai[30];
    int val,min,sek; // Finišavimo valanda, minutė ir sekundė

    ifstream fd("slidininkai_data.txt");
    fd>>n;
    fd.ignore();

    for(int i=0; i<n; i++)
    {
        getline(fd, Vardai[i], '\t');
        fd>>Valandos[i]>>Minutes[i]>>Sekundes[i];
        fd.ignore();
    }

    fd>>m;
    fd.ignore();

    for(int i=0; i<m; i++)
    {
        getline(fd, Finisuotojai[i], '\t');

        fd>>val>>min>>sek;
        fd.ignore();

        for(int j=0; j<n; j++)
            if(Vardai[j] == Finisuotojai[i])
                // Slidininkų, užtrunkančių daugiau 1 valandos, šalinimas
                if(val-Valandos[j] > 1)
                {
                    Vardai[j]=Vardai[n-1];
                    Valandos[j]=Valandos[n-1];
                    Minutes[j]=Minutes[n-1];
                    Sekundes[j]=Sekundes[n-1];
                    n--;
                    j--;
                }
                // Trukmės skaičiavimas
                else
                {
                    Minutes[j]=min-Minutes[j];
                    Sekundes[j]=sek-Sekundes[j];

                    if(Sekundes[j] < 0) {Sekundes[j]+=60; Minutes[j]--;}
                    if(Minutes[j] < 0) Minutes[j]+=60;
                }
    }
    fd.close();

    // Nefinišavusių slidininkų šalinimas ir pradinio sąrašo
    for(int i=0; i<n; i++)
    {
        bool kartojasi = false;
        for(int j=0; j<m; j++)
            if(Vardai[i] == Finisuotojai[j]) kartojasi = true;

        if(kartojasi == false)
        {
            Vardai[i]=Vardai[n-1];
            Minutes[i]=Minutes[n-1];
            Sekundes[i]=Sekundes[n-1];
            n--;
            i--;
        }
    }

    rikiuoti(n,m,Vardai,Minutes,Sekundes);
    rasyti(n,Vardai,Minutes,Sekundes);

    return 0;
}

void rikiuoti(int n, int m, string Vardai[], int Minutes[], int Sekundes[])
{
    for(int i=0; i<n-1; i++)
    {
        int laikas1=Minutes[i]*60+Sekundes[i];

        for(int j=i+1; j<m; j++)
        {
            int laikas2=Minutes[j]*60+Sekundes[j];

            if(laikas1 > laikas2)
            {
                swap(Vardai[i],Vardai[j]);
                swap(Minutes[i],Minutes[j]);
                swap(Sekundes[i],Sekundes[j]);
            }
            // Jei pasikartoja laikas, rikiuojami vardai abėcėlės tvarka
            if(laikas1 == laikas2)
                if(Vardai[i][0] > Vardai[j][0])
                {
                    swap(Vardai[i],Vardai[j]);
                    swap(Minutes[i],Minutes[j]);
                    swap(Sekundes[i],Sekundes[j]);
                }
        }
    }
}

void rasyti(int n, string Vardai[], int Minutes[], int Sekundes[])
{
    ofstream fr("slidininkai_rez.txt");
    for(int i=0; i<n; i++) fr<<Vardai[i]<<" "<<Minutes[i]<<" "<<Sekundes[i]<<endl;

    fr.close();
}
