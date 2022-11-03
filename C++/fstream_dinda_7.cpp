#include <fstream>
using namespace std;

int main()
{
    int n,sk,i,kiekis=0;
    ifstream fd("fstream_dinda_7_ivestis.txt");
    ofstream fr("fstream_dinda_7_isvestis.txt");
    fd>>n;
    for(i=1;i<=n;i++)
    {
        fd>>sk;
        if(sk==0)kiekis++;
    }
    if(kiekis>=2)fr<<"Yra bent du 0";
        else fr<<"Nera bent dvieju 0";

    fd.close();
    fr.close();
    return 0;
}
