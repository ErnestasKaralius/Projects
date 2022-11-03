#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int n,i,b,j;
    double s,suma,vsuma=0,kiekis=0;
    ifstream fd("butai_data.txt");
    ofstream fr("butai_rez.txt");
    fd>>n;
    for(i=1;i<=n;i++)
    {
        fd>>b;
        kiekis=kiekis+b;
        suma=0;
        for(j=1;j<=b;j++)
        {
            fd>>s;
            suma=suma+s;
        }
        vsuma=vsuma+suma;
        fr<<fixed<<setprecision(1)<<i<<" "<<suma/b<<endl;
    }
    fr<<fixed<<setprecision(1)<<vsuma/kiekis;

    fd.close();
    fr.close();
    return 0;
}
