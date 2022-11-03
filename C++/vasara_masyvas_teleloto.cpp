#include <fstream>
using namespace std;

int main()
{
    int n; // Pirkimų skaičius
    int S[52],L[52]; // Išlaidos ir laimėjimai
    int isuma=0,lsuma=0; // Išlaidų ir laimėjimų sumos
    int did; // Didžiausias laimėjimas
    int i;
    ifstream fd("teleloto_data.txt");
    ofstream fr("teleloto_rez.txt");
    fd>>n;
    // Nuskaitymas
    for(i=0;i<n;i++) fd>>S[i]>>L[i];

    // Didžiausio laimėjimo radimas ir sumų skaičiavimas
    did=L[0];
    for(i=0;i<n;i++)
    {
        isuma=isuma+S[i];
        lsuma=lsuma+L[i];
        if(L[i]>did) did=L[i];
    }
    fr<<isuma<<" Lt "<<lsuma<<" Lt";
    fr<<"\nDidžiausias laimėjimas: "<<did<<" Lt";
    fr<<"\nĮsigijo bilietų: "<<isuma/2;
    if(isuma<lsuma) fr<<"\nPelnas: "<<lsuma-isuma<<" Lt";
        else if(lsuma==isuma) fr<<"\nLygiosios";
            else fr<<"\nNuostolis: "<<isuma-lsuma<<" Lt";

    fd.close();
    fr.close();
    return 0;
}
