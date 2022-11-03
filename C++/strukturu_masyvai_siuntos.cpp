#include <fstream>
using namespace std;

struct siunta {
    string zyme;
    int x;
    int y;
    int z;
    double kaina;
};

struct firma {
    char Pavadinimas[26];
    int m;
    siunta S[100];
};

void skaitymas(firma F[], int&n, siunta&jono);
void rasymas(firma F[], int n, siunta jono);

bool ar_aptarnaus(int m, siunta S[], siunta jono);
siunta atitinkamos_radimas(int m, siunta S[], siunta jono);

int main()
{

    int n;
    firma F[100];
    siunta jono;

    skaitymas(F,n,jono);
    rasymas(F,n,jono);

    return 0;
}

void skaitymas(firma F[], int&n, siunta&jono)
{
    ifstream fd("siuntos_data.txt");

    fd>>n;
    fd.ignore();

    for(int i=0; i<n; i++)
    {
        fd.get(F[i].Pavadinimas, 25);
        fd>>F[i].m;
        fd.ignore();

        for(int j=0; j<F[i].m; j++)
        {
            fd>>F[i].S[j].zyme;
            fd>>F[i].S[j].x>>F[i].S[j].y>>F[i].S[j].z;
            fd>>F[i].S[j].kaina;
            fd.ignore();
        }
    }
    fd>>jono.x>>jono.y>>jono.z;

    fd.close();
}

bool ar_aptarnaus(int m, siunta S[], siunta jono)
{
    int kiekis=0;
    for(int i=0; i<m; i++)
        if(S[i].x < jono.x || S[i].y < jono.y || S[i].z < jono.z)
            kiekis++;

    if(kiekis==m) return false;

    return true;
}

siunta atitinkamos_radimas(int m, siunta S[], siunta jono)
{
    siunta tinka[100];
    int k=0;
    for(int i=0; i<m; i++)
        if(S[i].x >= jono.x && S[i].y >= jono.y && S[i].z >= jono.z)
        {
            tinka[k]=S[i];
            k++;
        }

    for(int i=0; i<k-1; i++)
        for(int j=i+1; j<k; j++)
            if(tinka[i].x * tinka[i].y * tinka[i].z > tinka[j].x * tinka[j].y * tinka[j].z)
                  swap(tinka[i], tinka[j]);

    return tinka[0];
}

void rasymas(firma F[], int n, siunta jono)
{
    ofstream fr("siuntos_rez.txt");

    siunta atitinkanti;
    for(int i=0; i<n; i++)
    {
        fr<<F[i].Pavadinimas<" ";
        if(ar_aptarnaus(F[i].m, F[i].S, jono))
        {
            atitinkanti=atitinkamos_radimas(F[i].m, F[i].S, jono);
            fr<<atitinkanti.zyme<<" "<<atitinkanti.x<<" "<<atitinkanti.y<<" "<<atitinkanti.z<<" "<<atitinkanti.kaina<<endl;
        }
        else fr<<"NEAPTARNAUS\n";
    }

    fr.close();
}
