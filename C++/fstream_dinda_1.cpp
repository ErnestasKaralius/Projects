#include <fstream>
using namespace std;

int main()
{
    int n,sk,i,suma=0;
    ifstream fd("fstream_dinda_1_ivestis.txt");
    ofstream fr("fstream_dinda_1_isvestis.txt");
    fd>>n;
    for(i=1;i<=n;i++)
    {
        fd>>sk;
        suma=suma+sk;
    }
    fr<<suma;

    fd.close();
    fr.close();
    return 0;
}
