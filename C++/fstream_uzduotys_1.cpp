#include <fstream>
using namespace std;

int main()
{
    int n,m,suma=0,i;
    ifstream fd("fstream_uzd_1_ivestis.txt");
    ofstream fr("fstream_uzd_1_isvestis.txt");
    fd>>n;
    for(i=1;i<=n;i++)
    {
        fd>>m;
        suma=suma+m;
    }
    fr<<suma;
    fd.close();
    fr.close();

    return 0;
}
