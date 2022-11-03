#include <fstream>
using namespace std;

void skaitymas(int&n, int Dienos[]);
void rasymas(int Dienos[]);

int daugiausia_skirtingu_geliu(int Dienos[]);
int paskutine_diena(int Dienos[], int did);

int main()
{
    int n;
    int Dienos[93];

    skaitymas(n,Dienos);
    rasymas(Dienos);

    return 0;
}

void skaitymas(int&n, int Dienos[])
{
    int nr;
    int pm, pd, gm, gd; // Pradžios ir pabaigos mėnuo, diena
    int pradzia, pabaiga;
    ifstream fd("geles_data.txt");

    // Žydinčių gėlių sk. nustatymas į 0
    for(int i=1; i<93; i++)
        Dienos[i] = 0;

    fd>>n;
    for(int i=0; i<n; i++)
    {
        fd>>nr>>pm>>pd>>gm>>gd;

        pradzia = pd;
        if(pm == 7) pradzia += 30;
            else if(pm == 8) pradzia += 61;

        pabaiga = gd;
        if(gm == 7) pabaiga += 30;
            else if(gm == 8) pabaiga += 61;

        for(int j=pradzia; j<pabaiga; j++)
            Dienos[j]++;
    }

    fd.close();
}

int daugiausia_skirtingu_geliu(int Dienos[])
{
    int did=1;

    for(int i=2; i<93; i++)
        if(Dienos[i] > Dienos[did])
            did = i;

    return did;
}

int paskutine_diena(int Dienos[], int did)
{
    for(int i=did; i<93; i++)
        if(Dienos[i] != Dienos[did])
            return i;
}

void rasymas(int Dienos[])
{
    ofstream fr("geles_rez.txt");

    int did = daugiausia_skirtingu_geliu(Dienos);
    fr<<Dienos[did]<<endl;

    if(did < 31) fr<<"6 "<<did<<endl;
        else if(did < 61) fr<<"7 "<<did - 30<<endl;
            else fr<<"8 "<<did - 61<<endl;

    did = paskutine_diena(Dienos,did);
    if(did < 31) fr<<"6 "<<did<<endl;
        else if(did < 61) fr<<"7 "<<did - 30<<endl;
            else fr<<"8 "<<did - 61<<endl;

    fr.close();
}
