#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int n,m,i,j,k=0;
    double sk,suma,psuma=0;
    ifstream fd("krepsinis_data.txt");
    ofstream fr("krepsinis_rez.txt");
    fd>>n;
    for(i=1;i<=n;i++)
    {
        suma=0;
        fd>>m;
        for(j=1;j<=m;j++)
        {
            fd>>sk;
            suma=suma+sk;
        }
        fr<<fixed<<setprecision(1)<<i<<" "<<suma/m<<endl;
        k=k+m;
        psuma=psuma+suma/m;
    }
    fr<<fixed<<setprecision(1)<<psuma/n<<" "<<k;

    fd.close();
    fr.close();
    return 0;
}
