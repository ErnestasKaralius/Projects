#include <fstream>
#include <string>
using namespace std;

void rikiuoti(int n, string Vardai[], int Numeris1[], int Valandos[], int Minutes[], int Sekundes[]);
void rasyti(int n, string Vardai[], int Numeris1[], int Valandos[], int Minutes[], int Sekundes[]);

int main()
{
    int n,m;
    char Vardas[21];
    string Vardai[30];

    int Numeris1[30];
    int Valandos[30],Minutes[30],Sekundes[30];

    int Numeris2[30];
    int val,min,sek;

    ifstream fd("sportas_data.txt");
    fd>>n;
    fd.ignore();
    for(int i=0; i<n; i++)
    {
        fd.get(Vardas,21);
        Vardai[i]=Vardas;
        fd>>Numeris1[i]>>Valandos[i]>>Minutes[i]>>Sekundes[i];
        fd.ignore();
    }
    fd>>m;
    for(int i=0; i<m; i++)
    {
        fd>>Numeris2[i];
        fd>>val>>min>>sek;

        int saudyklos;
        if(Numeris2[i]/100 == 2) saudyklos=4;
            else saudyklos=2;

        // Pridedamos minutės už kiekvieną nepataikymą
        int sk;
        for(int j=0; j<saudyklos; j++)
        {
            fd>>sk;
            min+=(5-sk);
        }

        // Trukmės skaičiavimas
        for(int j=0; j<n; j++)
            if(Numeris1[j] == Numeris2[i])
            {
                Sekundes[j]=sek-Sekundes[j];
                if(Sekundes[j] < 0) {Sekundes[j]=60+Sekundes[j]; min--;}

                val+=min/60; // Jei daugiau už 60 minučių, pridedamos valandos
                min%=60;

                Minutes[j]=min-Minutes[j];
                if(Minutes[j] < 0) {Minutes[j]=60+Minutes[j]; val--;}

                Valandos[j]=val-Valandos[j];
            }
    }
    fd.close();

    // Sportininkų, kurių nėra antrame sąraše, šalinimas
    for(int i=0; i<n; i++)
    {
        bool kartojasi=false;
        for(int j=0; j<m; j++)
            if(Numeris1[i] == Numeris2[j]) kartojasi=true;

        if(kartojasi == false)
        {
            Vardai[i]=Vardai[n-1];
            Numeris1[i]=Numeris1[n-1];
            Valandos[i]=Valandos[n-1];
            Minutes[i]=Minutes[n-1];
            Sekundes[i]=Sekundes[n-1];
            n--;
            i--;

        }
    }

    rikiuoti(n,Vardai,Numeris1,Valandos,Minutes,Sekundes);
    rasyti(n,Vardai,Numeris1,Valandos,Minutes,Sekundes);

    return 0;
}

void rikiuoti(int n, string Vardai[], int Numeris1[], int Valandos[], int Minutes[], int Sekundes[])
{
    for(int i=0; i<n-1; i++)
    {
        int laikas1 = Valandos[i]*3600+Minutes[i]*60+Sekundes[i];
        for(int j=i+1; j<n; j++)
        {
            int laikas2=Valandos[j]*3600+Minutes[j]*60+Sekundes[j];
            if(laikas1 > laikas2)
            {
                swap(Vardai[i], Vardai[j]);
                swap(Numeris1[i], Numeris1[j]);
                swap(Valandos[i], Valandos[j]);
                swap(Minutes[i], Minutes[j]);
                swap(Sekundes[i], Sekundes[j]);
            }

            laikas1=Valandos[i]*3600+Minutes[i]*60+Sekundes[i];
            laikas2=Valandos[j]*3600+Minutes[j]*60+Sekundes[j];

            if(laikas1 == laikas2 && Numeris1[i]/100 == Numeris1[j]/100 && Vardai[i][0] > Vardai[j][0])
            {
                swap(Vardai[i], Vardai[j]);
                swap(Numeris1[i], Numeris1[j]);
                swap(Valandos[i], Valandos[j]);
                swap(Minutes[i], Minutes[j]);
                swap(Sekundes[i], Sekundes[j]);
            }
        }
    }
}

void rasyti(int n, string Vardai[], int Numeris1[], int Valandos[], int Minutes[], int Sekundes[])
{
    ofstream fr("sportas_rez.txt");
    fr<<"Merginos\n";
    for(int i=0; i<n; i++)
        if(Numeris1[i]/100 == 1) fr<<Numeris1[i]<<" "<<Vardai[i]<<Valandos[i]<<" "<<Minutes[i]<<" "<<Sekundes[i]<<endl;

    fr<<"Vaikinai\n";
    for(int i=0; i<n; i++)
        if(Numeris1[i]/100 == 2) fr<<Numeris1[i]<<" "<<Vardai[i]<<Valandos[i]<<" "<<Minutes[i]<<" "<<Sekundes[i]<<endl;

    fr.close();
}
