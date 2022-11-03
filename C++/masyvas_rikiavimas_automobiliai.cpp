#include <fstream>
using namespace std;

int main()
{
    int n,g; // Kolekcininkų ir grupių skaičius
    int G[6],M[6]; // Grupių ir modeliukų masyvas
    int sk; // Modeliuko dydis
    int suma=0; // Modeliukų suma
    int did,maz;
    int dvieta=0,mvieta=0;
    int i,j;
    ifstream fd("automoboliu_modeliai_data.txt");
    ofstream fr("automoboliu_modeliai_rez.txt");
    fd>>n>>g;
    //Lentynų talpos idėjimas į masyvą
    for(i=0;i<g;i++) fd>>G[i];
    // Pirmosios modeliukų eilės idėjimas į masyvą
    for(i=0;i<g;i++) fd>>M[i];

    // Modeliukų grupės sumos skaičiavimas
    for(i=2;i<=n;i++)
        for(j=0;j<g;j++)
        {
            fd>>sk;
            M[j]=M[j]+sk;
        }

    // Reikalingų lentynų skaičiaus radimas
    for(i=0;i<g;i++)
    {
        G[i]=M[i]/G[i];
        if(M[i]%G[i]!=0) G[i]++;

        suma=suma+G[i];
        fr<<M[i]<<" "<<G[i]<<endl;
    }
    fr<<suma<<endl;

    did=G[0];
    maz=G[0];
    // Kuriam modeliukui reikia daugiausiai ir mažiausiai lentynų
    for(i=1;i<g;i++)
    {
        if(G[i]>did) {did=G[i]; dvieta=i;}
        if(G[i]<maz) {maz=G[i]; mvieta=i;}
    }
    fr<<dvieta+1<<" "<<mvieta+1;
    return 0;
}
