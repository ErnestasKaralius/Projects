#include <fstream>
using namespace std;

int main()
{
    int n,i,sk,k,kiekis=0;
    ifstream fd("fstream_dinda_5_ivestis.txt");
    ofstream fr("fstream_dinda_5_isvestis.txt");
    fd>>n>>k;
    for(i=2;i<=n;i++)
    {
        fd>>sk;
        if(sk<k) kiekis++;
        k=sk;
    }
    fr<<kiekis;

    fd.close();
    fr.close();
    return 0;
}
