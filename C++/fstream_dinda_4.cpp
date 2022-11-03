#include <fstream>
using namespace std;

int main()
{
    int n,sk,i,suma=0;
    ifstream fd("fstream_dinda_4_ivestis.txt");
    ofstream fr("fstream_dinda_4_isvestis.txt");
    fd>>n;
    for(i=1;i<=n;i++)
    {
        fd>>sk;
        if(sk%2==1&&sk%7==0&&sk%10==1)suma++;
    }
    fr<<suma;

    fd.close();
    fr.close();
    return 0;
}
