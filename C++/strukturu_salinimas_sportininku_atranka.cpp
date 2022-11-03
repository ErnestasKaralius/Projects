#include <fstream>
#include <string>
using namespace std;

struct sportininkas {
    char Vardas[26];
    string komanda;
    int sp;
    int st;
};

void skaitymas(int&eiles, int&p, int&t, sportininkas S[]);
void salinimas(int&eiles, int p, int t, sportininkas S[]);
void rasymas(int eiles, sportininkas S[]);

int main()
{
    int p,t;
    int eiles=0;
    sportininkas S[50];

    skaitymas(eiles,p,t,S);
    salinimas(eiles,p,t,S);
    rasymas(eiles,S);

    return 0;
}

void skaitymas(int&eiles, int&p, int&t, sportininkas S[])
{
    ifstream fd("sportininku_atranka_data.txt");
    fd>>p>>t;
    fd.ignore();
    while(!fd.eof())
    {
        fd.get(S[eiles].Vardas, 26);
        fd>>S[eiles].komanda;
        fd>>S[eiles].sp>>S[eiles].st;
        fd.ignore();
        eiles++;
    }

    fd.close();
}

void salinimas(int&eiles, int p, int t, sportininkas S[])
{
    for(int i=0; i<eiles; i++)
        if(S[i].sp <= p || S[i].st < t)
        {
            for(int j=i; j<eiles-1; j++)
                S[j]=S[j+1];

            eiles--;
            i--;
        }
}

void rasymas(int eiles, sportininkas S[])
{
    ofstream fr("sportininku_atranka_rez.txt");

    for(int i=0; i<eiles; i++)
        fr<<S[i].Vardas<<" "<<S[i].komanda<<" "<<S[i].sp<<" "<<S[i].st<<endl;

    fr.close();
}
