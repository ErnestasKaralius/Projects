#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int t,i,s,j,k,sk,bsk=0;
    double vk,kaina,bkaina=0;
    ifstream fd("elektronika_data.txt");
    ofstream fr("elektronika_rez.txt");
    fd>>t;
    for(i=1;i<=t;i++)
    {
        kaina=0;
        sk=0;
        fd>>s;
        for(j=1;j<=s;j++)
        {
            fd>>k>>vk;
            sk=sk+k;
            kaina=kaina+vk*k;
        }
        bsk=bsk+sk;
        bkaina=bkaina+kaina;
        fr<<fixed<<setprecision(2)<<sk<<" "<<kaina<<endl;
    }
    fr<<fixed<<setprecision(2)<<bsk<<" "<<bkaina;

    fd.close();
    fr.close();
    return 0;
}
