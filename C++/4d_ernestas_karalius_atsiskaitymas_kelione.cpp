#include <fstream>
using namespace std;
int reiks_isipilti_kartu(int s,int b);
int keliones_trukme(int s,int v);

int main()
{
    int b;
    int s,v;
    ifstream fd("kelione2.txt");
    ofstream fr("kelione_rez.txt");
    fd>>b;
    fd>>s>>v;
    int laikas1=keliones_trukme(s,v)+reiks_isipilti_kartu(s,b)*5;
    fd>>s>>v;
    int laikas2=keliones_trukme(s,v)+reiks_isipilti_kartu(s,b)*5;
    fr<<"Pirmu keliu: "<<laikas1/60<<"h "<<laikas1%60<<"min"<<endl;
    fr<<"Antru keliu: "<<laikas2/60<<"h "<<laikas2%60<<"min"<<endl;

    if(laikas1<laikas2) fr<<"Pirmu keliu greičiau";
        else if(laikas2<laikas1) fr<<"Antru keliu greičiau";
            else fr<<"Abiem kelias laikas nesiskiria";

    fd.close();
    fr.close();
    return 0;
}

int reiks_isipilti_kartu(int s,int b)
{
    int kartai=s/b;
    if(s%b!=0) kartai++;

    return kartai;
}

int keliones_trukme(int s,int v)
{
    int trukme=(double)s/v*60;

    return trukme;
}



