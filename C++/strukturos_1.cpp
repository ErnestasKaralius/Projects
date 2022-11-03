#include <fstream>
#include <iostream>
using namespace std;

struct laikas {
    int d;
    int val;
    int min;
    int sek;

};

void skaitymas(struct laikas&s, struct laikas&f);
bool ar_lygus(struct laikas s, struct laikas f);
bool ar_trumpesnis(struct laikas s, struct laikas f);
void laiko_tarpu_suma(struct laikas s, struct laikas&f);

int main()
{
    laikas s,f;

    skaitymas(s,f);
    cout<<ar_lygus(s,f)<<endl;
    if(ar_trumpesnis(s,f) == 1) cout<<"Pirmas laiko tarpas yra mazesnis uz antra\n";
        else cout<<"Pirmas laiko tarpas nera mazesnis uz antra\n";

    laiko_tarpu_suma(s,f);

    cout<<f.d<<" "<<f.val<<" "<<f.min<<" "<<f.sek;

    return 0;
}

void skaitymas(struct laikas&s, struct laikas&f)
{
    ifstream fd("strukturos_1_data.txt");

    fd>>s.d>>s.val>>s.min>>s.sek;
    fd>>f.d>>f.val>>f.min>>f.sek;

    fd.close();
}

bool ar_lygus(struct laikas s, struct laikas f)
{
    if(s.d == f.d && s.val == f.val && s.min == f.min && s.sek == f.sek) return true;
        else return false;
}

bool ar_trumpesnis(struct laikas s, struct laikas f)
{
    double laikas1 = s.d*1440 + s.val*60 + s.min +(double)s.sek/60;
    double laikas2 = f.d*1440 + f.val*60 + f.min +(double)f.sek/60;

    if(laikas1 < laikas2) return true;
        else return false;
}

void laiko_tarpu_suma(struct laikas s, struct laikas&f)
{
    f.d += s.d;
    f.val += s.val;
    f.min += s.min;
    f.sek += s.sek;

    f.min = f.min + f.sek/60;
    f.sek = f.sek%60;

    f.val = f.val + f.min/60;
    f.min = f.min%60;

    f.d = f.d + f.val/24;
    f.val = f.val%24;
}
