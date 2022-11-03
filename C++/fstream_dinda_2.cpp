#include <fstream>
using namespace std;

int main()
{
    int n,t,i;
    bool r;
    ifstream fd("fstream_dinda_2_ivestis.txt");
    ofstream fr("fstream_dinda_2_isvestis.txt");
    fd>>n;
    for(i=1;i<=n;i++)
    {
        fd>>t;
        if(t<0)r=1;
    }
    if(r==1)fr<<"TAIP";
        else fr<<"NE";

    fd.close();
    fr.close();
    return 0;
}
