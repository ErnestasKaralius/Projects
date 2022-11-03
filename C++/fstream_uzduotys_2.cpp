#include <fstream>
using namespace std;

int main()
{
    int n,i;
    double p,suma=0;
    ifstream fd("fstream_uzd_2_ivestis.txt");
    ofstream fr("fstream_uzd_2_isvestis.txt");
    fd>>n;
    for(i=1;i<=n;i++)
    {
        fd>>p;
        suma=suma+p;
    }
    fr<<suma<<endl;
    fr<<suma/n;

    fd.close();
    fr.close();
    return 0;
}
