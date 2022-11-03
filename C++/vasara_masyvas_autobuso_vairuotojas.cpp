#include <fstream>
using namespace std;

int main()
{
    int K[20]; // Kiekvienos dienos kilometrai
    int s,m; // Kiek reikia nuvažiuoti ir atlyginimas
    int suma=0; // Kilometrų suma
    int v=0,a=0,p=0; // Viršijo, atsiliko, pažeidė dienų
    int did=0,sk,d; // Labiausia pažeidžiama diena, pažeidimo reikšmė, diena
    int i;
    ifstream fd("vairuotojas_data.txt");
    ofstream fr("vairuotojas_rez.txt");
    fd>>s>>m;
    // Nuskaitymas
    for(i=0;i<20;i++) fd>>K[i];

    // Vidurkio radimas
    for(i=0;i<20;i++) suma=suma+K[i];
    fr<<"Vidutiniškai nuvažiuoja per dieną: "<<(double)suma/20;

    for(i=0;i<20;i++)
    {
        // Kiek viršijo ir atsiliko
        if(K[i]>s) v++;
            else if(K[i]<s) a++;

        // Didesnis už x*1.2
        if(K[i]>=s*1.2)
        {
            p++; // Kiek pažeidė
            sk=K[i]-s*1.2; // Pažeidimo dydis
            m=m-sk; // Liko pinigų
        }
        // Mažesnis už x*0.2
        else if(K[i]<=s*0.8)
        {
            p++;
            sk=s*0.8-K[i];
            m=m-sk;
        }
        if(sk>did) {did=sk;d=i+1;}
    }

    fr<<"\nViršijama dienų: "<<v;
    fr<<"\nAtsiliekama dienų: "<<a;
    fr<<"\nRežimas pažeidžiamas dienų: "<<p;
    fr<<"\nDiena, kurią režimas pažeidžiamas labiausiai: "<<d;
    fr<<"\nGalutinis atlyginimas: "<<m;

    fd.close();
    fr.close();
    return 0;
}
