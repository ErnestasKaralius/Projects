#include <fstream>
using namespace std;

int main()
{
    int n,sk,i,suma=0;
    ifstream fd("fstream_dinda_3_ivestis.txt");
    ofstream fr("fstream_dinda_3_isvestis.txt");
    fd>>n;
    for(i=1;i<=n;i++)
    {
        fd>>sk;
        if(sk%2==1)suma++;
    }
    fr<<suma;

    fd.close();
    fr.close();
    return 0;
}
