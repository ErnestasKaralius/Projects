#include <fstream>
using namespace std;

int main()
{
    int n,k,i,j;
    double m1,m2,k1,k2,S=0,bendras=0;
    ifstream fd("fstream_dinda_5_87_ivestis.txt");
    ofstream fr("fstream_dinda_5_87_isvestis.txt");
    fd>>n;
    for(i=1;i<=n;i++)
    {
        fd>>k;
        fd>>m1>>m2;
        for(j=1;j<=k;j++)
        {
            fd>>k1>>k2;
            S=S+k1*k2;
        }
        S=m1*m2-S;
        bendras=bendras+S;
        fr<<S<<endl;
        S=0;
    }
    fr<<"Iš viso: "<<bendras;

    fd.close();
    fr.close();
    return 0;
}
