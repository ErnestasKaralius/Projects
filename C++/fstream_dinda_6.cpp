#include <fstream>
using namespace std;

int main()
{
    int n,i,sk,k;
    bool s=1;
    ifstream fd("fstream_dinda_6_ivestis.txt");
    ofstream fr("fstream_dinda_6_isvestis.txt");
    fd>>n>>k;
    for(i=2;i<=n;i++)
    {
        fd>>sk;
        if(sk<k) s=0;
        k=sk;
    }
    if(s==0)fr<<"Seka nera didejanti";
        else fr<<"Seka didejanti";

    fd.close();
    fr.close();
    return 0;
}
