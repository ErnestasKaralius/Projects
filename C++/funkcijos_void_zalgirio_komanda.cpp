#include <fstream>
using namespace std;
void skaitymas(int&s, int&n, int S[], int N[]);
void rasymas(int s, int n, int S[]);

void iterpimas(int s, int n, int S[], int N[]);

int main()
{
    int s,n; // Senbuvių ir naujokų skaičius
    int S[200],N[100]; // Senbuvių ir naujokų masyvas

    skaitymas(s,n,S,N);
    iterpimas(s,n,S,N);
    rasymas(s,n,S);

    return 0;
}

void skaitymas(int&s, int&n, int S[], int N[])
{
    ifstream fs("zalgirio_komanda_senbuviai.txt");
    fs>>s;
    for(int i=0;i<s;i++) fs>>S[i];

    fs.close();

    ifstream fn("zalgirio_komanda_naujokai.txt");
    fn>>n;
    for(int i=0;i<n;i++) fn>>N[i];

    fn.close();
}

void iterpimas(int s, int n, int S[], int N[])
{
    for(int i=0;i<n;i++)
        for(int j=0;j<s;j++)
        {
            if(N[i]>S[0])
            {
                for(int e=s;e>0;e--) S[e]=S[e-1];
                S[0]=N[i];
                s++;
                break;
            }
            if(N[i]<S[s-1])
            {
                S[s]=N[i];
                s++;
                break;
            }
            if(N[i]>=S[j+1]&&N[i]<=S[j])
            {
                for(int e=s;e>j;e--) S[e]=S[e-1];
                S[j+1]=N[i];
                s++;
                break;
            }
        }
}

void rasymas(int s, int n, int S[])
{
    ofstream fr("funkcijos_zalgirio_komanda_rez.txt");
    for(int i=0;i<s+n;i++) fr<<S[i]<<"\n";

    fr.close();
}
