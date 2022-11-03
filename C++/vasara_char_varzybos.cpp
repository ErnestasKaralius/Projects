#include <fstream>
using namespace std;

int main()
{
    char L[30],S[30]; // Lytis, sporto šaka
    int U[30]; // Ūgis
    int n; // Mokinių skaičius
    int sk=0; // Žaidžiančių mokinių skaičius
    int v=0,m=0; // Merginių ir vaikinų skaičius
    int sum=0; // Ūgių suma
    int i,j;
    ifstream fd ("varzybos_data.txt");
    ofstream fr ("varzybos_rez.txt");
    fd>>n;
    // Nuskaitymas
    for(i=0;i<n;i++) fd>>L[i]>>U[i]>>S[i];
    // Nes tik 3 sporto šakos
    for(j=1;j<=3;j++)
    {
        // Kiekvienos sporto šakos sudėtis bei skaičius
        for(i=0;i<n;i++)
            if(j==1&&S[i]=='K')
            {
                sum=sum+U[i];
                sk++;
                if(L[i]=='M') m++;
                    else v++;
            }
            else if(j==2&&S[i]=='T')
            {
                sk++;
                if(L[i]=='M') m++;
                    else v++;
            }
            else if(j==3&&S[i]=='F')
            {
                sk++;
                if(L[i]=='M') m++;
                    else v++;
            }
        fr<<"\nŽaidžia: "<<sk;
        // Jei galima sudaryti
        if(sk>=7)
        {
            fr<<"\nVaikinų: "<<v<<", merginų: "<<m<<endl;
            // Kiekvieno komandos nario duomenų išspausdinimas
            for(i=0;i<n;i++)
                if(j==1&&S[i]=='K') fr<<L[i]<<" "<<U[i]<<" "<<S[i]<<endl;
                    else if(j==2&&S[i]=='T') fr<<L[i]<<" "<<U[i]<<" "<<S[i]<<endl;
                        else if(j==3&&S[i]=='F') fr<<L[i]<<" "<<U[i]<<" "<<S[i]<<endl;

            if(j==1)fr<<"Ūgio vidurkis: "<<sum/sk<<endl;

        }
        else fr<<"\nKomandos sudaryti negalės\n";
        v=0; m=0; sk=0;
    }
    // Palaikymo grupės narių skaičius, sudėtis
    for(i=0;i<n;i++)
        if(S[i]=='S')
        {
            sk++;
            if(L[i]=='M') m++;
                else v++;
        }
    fr<<"\nPalaiko: "<<sk;
    fr<<"\nVaikinų: "<<v<<", merginų: "<<m<<endl;
    for(i=0;i<n;i++) if(S[i]=='S') fr<<L[i]<<" "<<U[i]<<" "<<S[i]<<endl;


    fd.close();
    fr.close();
    return 0;
}
