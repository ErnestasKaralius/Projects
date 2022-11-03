#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

struct stotele {
    char Pavadinimas[16];
    double atstumas;
    int valandos;
    int minutes;
};

void skaitymas(int&n, double&greitis, int&val, int&min, stotele S[]);
void atvykimo_laikas(int n, double greitis, int val, int min, stotele S[]);
int laikas_iveikti(double greitis, double atstumas);
void rasymas(int n, stotele S[]);

int main()
{
    int n;
    double greitis;
    int val,min;
    stotele S[100];

    skaitymas(n,greitis,val,min,S);
    atvykimo_laikas(n,greitis,val,min,S);
    rasymas(n,S);

    cout<<abs(-10);

    return 0;
}

void skaitymas(int&n, double&greitis, int&val, int&min, stotele S[])
{
    ifstream fd("kelione_data.txt");

    fd>>n;
    fd>>greitis;
    fd>>val>>min;

    fd.ignore();

    for(int i=0; i<n; i++)
    {
        fd.get(S[i].Pavadinimas, 15);
        fd>>S[i].atstumas;

        fd.ignore();
    }
    fd.close();
}

void atvykimo_laikas(int n, double greitis, int val, int min, stotele S[])
{
    int m = laikas_iveikti(greitis, S[0].atstumas);
    S[0].minutes = (min + m) % 60;
    S[0].valandos = (min + m) / 60 + val;

    for(int i=1; i<n; i++)
    {
        m = laikas_iveikti(greitis, S[i].atstumas);

        S[i].minutes = (S[i-1].minutes + m) % 60;
        S[i].valandos = (S[i-1].minutes + m) / 60 + S[i-1].valandos;

    }
}

int laikas_iveikti(double greitis, double atstumas)
{
    int laikas = atstumas / greitis * 60;

    return laikas;
}

void rasymas(int n, stotele S[])
{
    ofstream fr("kelione_rez.txt");

    for(int i=0; i<n; i++)
        fr<<S[i].Pavadinimas<<" "<<S[i].valandos<<" val. "<<S[i].minutes<<" min.\n";

    fr.close();
}
