#include <fstream>
using namespace std;

struct savivaldybe {
    string pavadinimas;
    int n; // Mokyklų skaičius
    string apskritis;
    int s; // Savivaldybių skaičius
};

void skaitymas(int&k, savivaldybe S[]);
void salinimas(int&k, savivaldybe S[]);
void rikiavimas(int k, savivaldybe S[]);
void rasymas(int k, savivaldybe S[]);

int main()
{
    int k;
    savivaldybe S[60];

    skaitymas(k,S);
    salinimas(k,S);
    rikiavimas(k,S);
    rasymas(k,S);

    return 0;
}
void skaitymas(int&k, savivaldybe S[])
{
    ifstream fd("savivaldybes_data.txt");
    fd>>k;
    for(int i=0; i<k; i++)
    {
        fd>>S[i].pavadinimas;
        fd>>S[i].n;
        fd>>S[i].apskritis;
        S[i].s = 1;
    }

    fd.close();
}

void salinimas(int&k, savivaldybe S[])
{
    for(int i=0; i<k-1; i++)
        for(int j=i+1; j<k; j++)
            if(S[i].apskritis == S[j].apskritis)
            {
                S[i].s++;
                if(S[j].n > S[i].n)
                    S[i].n = S[j].n;

                S[j] = S[k-1];
                k--;
                j--;
            }
}

void rikiavimas(int k, savivaldybe S[])
{
    for(int i=0; i<k-1; i++)
        for(int j=i+1; j<k; j++)
            if(S[i].n < S[j].n)
                swap(S[i],S[j]);
}

void rasymas(int k, savivaldybe S[])
{
    ofstream fr("savivaldybes_rez.txt");

    for(int i=0; i<k; i++)
        fr<<S[i].apskritis<<" "<<S[i].s<<" "<<S[i].n<<"\n";

    fr.close();
}
