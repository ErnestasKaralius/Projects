#include <fstream>
using namespace std;

struct keleivis {
    char Pavarde[21];
    int k;
    double mase;
};

void skaitymas(int&n, keleivis K[], int&m, int&x, int&y);
void rasymas(int n, keleivis K[], int m, int x, int y);

int keleiviai_nevirsijantys_vienetu(int n, keleivis K[], int m);

int keleiviu_skaicius(int n, keleivis K[], int sk);
int vidurkis(int n, keleivis K[]);

bool skiriasi_y_kilogramu(double did, double mase, int y);
double didziausia_mase(int n, keleivis K[]);

int main()
{
    int n;
    keleivis K[500];
    int m,x,y;

    skaitymas(n,K,m,x,y);
    rasymas(n,K,m,x,y);

    return 0;
}

void skaitymas(int&n, keleivis K[], int&m, int&x, int&y)
{
    ifstream fd("lektuvo_bagazas_data.txt");
    fd>>n;
    fd.ignore();
    for(int i=0; i<n; i++)
    {
        fd.get(K[i].Pavarde, 21);
        fd>>K[i].k;

        double suma=0,sk;
        for(int j=0; j<K[i].k; j++)
        {
            fd>>sk;
            suma+=sk;
        }
        K[i].mase = suma;

        fd.ignore();
    }
    fd>>m>>x>>y;

    fd.close();
}

int keleiviai_nevirsijantys_vienetu(int n, keleivis K[], int m)
{
    int kiekis=0;

    for(int i=0; i<n; i++)
        if(K[i].k <= m) kiekis++;

    return kiekis;
}

int keleiviu_skaicius(int n, keleivis K[], int sk)
{
    int kiekis=0;

    for(int i=0; i<n; i++)
        if(K[i].mase > sk) kiekis++;

    return kiekis;
}

int vidurkis(int n, keleivis K[])
{
    double suma=0;

    for(int i=0; i<n ;i++)
        suma+=K[i].mase;

    return suma/n;
}

bool skiriasi_y_kilogramu(double did, double mase, int y)
{
    if(did-y == mase || did+y == mase) return true;

    return false;
}

double didziausia_mase(int n, keleivis K[])
{
    double did=K[0].mase;

    for(int i=1; i<n; i++)
        if(K[i].mase > did) did=K[i].mase;

    return did;
}

void rasymas(int n, keleivis K[], int m, int x, int y)
{
    ofstream fr("lektuvo_bagazas_rez.txt");

    fr<<keleiviai_nevirsijantys_vienetu(n,K,m)<<endl;
    fr<<keleiviu_skaicius(n,K,x)<<endl;
    fr<<keleiviu_skaicius(n,K,vidurkis(n,K))<<endl;

    for(int i=0; i<n; i++)
        if(skiriasi_y_kilogramu(didziausia_mase(n,K),K[i].mase,y))
            fr<<K[i].Pavarde<<endl;

    fr.close();


}


