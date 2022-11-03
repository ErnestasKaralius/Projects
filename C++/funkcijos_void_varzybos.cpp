#include <fstream>
using namespace std;
void skaitymas(int&n, char L[], int U[], char S[]);
void rasymas(int n, char L[], int U[], char S[]);

void komandos_sudetis(int n, char s, char L[],int U[],char S[], int&kiekis,int&vkiekis,int&mkiekis);
int ugiu_vidurkis(int n, int kiekis, char S[], int U[]);

int main()
{
    int n; // Mokinių skaičius
    char L[30],S[30]; // Lytis, sporto šaka
    int U[30]; // Ūgiai

    skaitymas(n,L,U,S);
    rasymas(n,L,U,S);

    return 0;
}

void skaitymas(int&n, char L[], int U[], char S[])
{
    ifstream fd("sportines_varzybos_data.txt");
    fd>>n;
    for(int i=0;i<n;i++) fd>>L[i]>>U[i]>>S[i];

    fd.close();
}

void komandos_sudetis(int n, char s, char L[],int U[],char S[], int&kiekis,int&vkiekis,int&mkiekis)
{
    kiekis=0; vkiekis=0; mkiekis=0;
    for(int i=0;i<n;i++)
        if(S[i]==s)
        {
            kiekis++;
            if(L[i]=='V') vkiekis++;
                else mkiekis++;
        }
}

int ugiu_vidurkis(int n, int kiekis, char S[], int U[])
{
    int suma=0;
    for(int i=0;i<n;i++) if(S[i]=='K') suma=suma+U[i];

    int vidurkis=suma/kiekis;
}

void rasymas(int n, char L[], int U[], char S[])
{
    int kiekis,vkiekis,mkiekis;
    ofstream fr("sportines_varzybos_rez.txt");

    // Krepšinio komanda
    komandos_sudetis(n,'K',L,U,S,kiekis,vkiekis,mkiekis);
    fr<<"Krepšinio komandą sudaro: "<<kiekis<<endl;
    if(kiekis>=7)
    {
        fr<<"Vaikinų: "<<vkiekis<<" Merginų: "<<mkiekis<<endl;
        for(int i=0;i<n;i++)
            if(S[i]=='K') fr<<L[i]<<" "<<U[i]<<" "<<S[i]<<endl;

        fr<<"Ūgių vidurkis: "<<ugiu_vidurkis(n,kiekis,S,U)<<endl;;
    }
    else fr<<"Krepšinio komandos sudaryti negalima"<<endl;

    // Tinklinio komanda
    komandos_sudetis(n,'T',L,U,S,kiekis,vkiekis,mkiekis);
    fr<<"Tinklinio komandą sudaro: "<<kiekis<<endl;
    if(kiekis>=7)
    {
        fr<<"Vaikinų: "<<vkiekis<<" Merginų: "<<mkiekis<<endl;
        for(int i=0;i<n;i++)
            if(S[i]=='T') fr<<L[i]<<" "<<U[i]<<" "<<S[i]<<endl;
    }
    else fr<<"Tinklinio komandos sudaryti negalima"<<endl;

    // Futbolo komanda
    komandos_sudetis(n,'F',L,U,S,kiekis,vkiekis,mkiekis);
    fr<<"Futbolo komandą sudaro: "<<kiekis<<endl;
    if(kiekis>=12)
    {
        fr<<"Vaikinų: "<<vkiekis<<" Merginų: "<<mkiekis<<endl;
        for(int i=0;i<n;i++)
            if(S[i]=='F') fr<<L[i]<<" "<<U[i]<<" "<<S[i]<<endl;
    }
    else fr<<"Futbolo komandos sudaryti negalima"<<endl;

    // Palaikymo komanda
    komandos_sudetis(n,'S',L,U,S,kiekis,vkiekis,mkiekis);
    fr<<"Plaikymo komandą sudaro: "<<kiekis<<endl;
    fr<<"Vaikinų: "<<vkiekis<<" Merginų: "<<mkiekis<<endl;
        for(int i=0;i<n;i++)
            if(S[i]=='S') fr<<L[i]<<" "<<U[i]<<" "<<S[i]<<endl;

    fr.close();
}
