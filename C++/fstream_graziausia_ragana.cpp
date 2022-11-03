#include <fstream>
using namespace std;

int main()
{
    int n,m,i,j,sk,suma,maz,eil=1;
    ifstream fd("ragana_data.txt");
    ofstream fr("ragana_rez.txt");
    fd>>n>>m;
    for(i=1;i<=n;i++)
    {
        suma=0;
        for(j=1;j<=m;j++)
        {
            fd>>sk;
            suma=suma+sk;
        }
        fr<<i<<" "<<suma<<endl;
        if(i==1) maz=suma;
            else if(suma<maz){maz=suma;eil=i;}
    }
    fr<<eil;

    fd.close();
    fr.close();
    return 0;
}
