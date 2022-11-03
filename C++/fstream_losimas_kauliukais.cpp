#include <fstream>
using namespace std;

int main()
{
    int n,i,k,j,sk,suma,vieta,dsk;
    ifstream fd("kauliukai_data.txt");
    ofstream fr("kauliukai_rez.txt");
    fd>>n;
    for(i=1;i<=n;i++)
    {
        suma=0;
        fd>>k;
        for(j=1;j<=k;j++)
        {
            fd>>sk;
            suma=suma+sk;
        }
        if(sk%2==0)j=k+1;
        if(i==1){vieta=i;dsk=suma;}
        if(suma>dsk){vieta=i;dsk=suma;}
        fr<<i<<" "<<suma<<endl;
    }
    fr<<vieta;

    fd.close();
    fr.close();
    return 0;
}
