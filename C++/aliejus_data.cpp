#include <fstream>
using namespace std;

struct indas {
    int pradinis;
    int pripildyta;
    int nepanaudota;
    int talpa;
    int reikia;
};

struct pinigai {
    int islaidos;
    int kaina1;
    int kaina3;
    int kaina5;
};

void skaitymas(indas&n1, indas&n3, indas&n5, int&k, pinigai&pelnas);
void indu_pripildymas(indas&n, int&k);
void rasymas(indas n1, indas n3, indas n5, int k, pinigai pelnas);

int main()
{
    indas n1, n3, n5;
    int k;
    pinigai pelnas;

    skaitymas(n1,n3,n5,k,pelnas);
    indu_pripildymas(n5,k);
    indu_pripildymas(n3,k);
    indu_pripildymas(n1,k);
    rasymas(n1,n3,n5,k,pelnas);


    return 0;
}

void skaitymas(indas&n1, indas&n3, indas&n5, int&k, pinigai&pelnas)
{
    ifstream fd("aliejus_data.txt");

    fd>>n1.pradinis>>n3.pradinis>>n5.pradinis;
    fd>>k;
    fd>>pelnas.islaidos>>pelnas.kaina1>>pelnas.kaina3>>pelnas.kaina5;

    n1.talpa = 1; n3.talpa = 3; n5.talpa = 5;

    fd.close();
}

void indu_pripildymas(indas&n, int&k)
{
    int reikia = k / n.talpa;

    if(reikia > n.pradinis) {k -= n.pradinis * n.talpa; n.pripildyta = n.pradinis;}
        else {k -= reikia * n.talpa; n.pripildyta = reikia;}
}

void rasymas(indas n1, indas n3, indas n5, int k, pinigai pelnas)
{
    ofstream fr("aliejus_rez.txt");

    fr<<n1.pripildyta<<" "<<n3.pripildyta<<" "<<n5.pripildyta<<" "<<k<<"\n";

    n1.nepanaudota = n1.pradinis - n1.pripildyta;
    n3.nepanaudota = n3.pradinis - n3.pripildyta;
    n5.nepanaudota = n5.pradinis - n5.pripildyta;
    fr<<n1.nepanaudota<<" "<<n3.nepanaudota<<" "<<n5.nepanaudota<<"\n";

    n5.reikia = k / 5; k %= 5;
    n3.reikia = k / 3; k %= 3;
    n1.reikia = k / 1;
    fr<<n1.reikia<<" "<<n3.reikia<<" "<<n5.reikia<<"\n";

    fr<<((n1.pripildyta + n1.reikia) * pelnas.kaina1 + (n3.pripildyta + n3.reikia) * pelnas.kaina3 + (n5.pripildyta + n5.reikia) * pelnas.kaina5) - pelnas.islaidos;

    fr.close();
}
