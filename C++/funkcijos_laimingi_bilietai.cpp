#include <fstream>
#include <cmath>
using namespace std;
int atbulas_skaicius(int n,int m);

int main()
{
    int n,m;
    int kiekis=0;
    ifstream fd("laimingi_bilietai_data.txt");
    ofstream fr("laimingi_bilietai_rez.txt");
    fd>>n>>m;
    for(n;n<=m;n++) if(atbulas_skaicius(n,m)==n) kiekis++;
    fr<<kiekis;

    fd.close();
    fr.close();
    return 0;
}

int atbulas_skaicius(int n,int m)
{
    // Laipsnio skaičiavimas su skaitmenų-1 kiekiu
    int laipsnis=0;
    int sk=n/10;
    while(sk!=0) {sk=sk/10; laipsnis++;}

    // Atbulo skaičiaus formavimas
    int daugiklis=pow(10,laipsnis);
    int apverstas_skaitmuo=0;
    sk=n;
    while(sk!=0)
    {
        apverstas_skaitmuo=apverstas_skaitmuo+sk%10*daugiklis;
        sk=sk/10;
        daugiklis=daugiklis/10;
    }
    return apverstas_skaitmuo;
}
