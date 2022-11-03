#include <fstream>
using namespace std;
int main()
{
    int a,b,i,j;
    ifstream fd("trikampis_data.txt");
    ofstream fr("trikampis_rez.txt");
    fd>>a>>b;
    for(i=a;i<=b;i++)
        for(j=i+1;j<=b;j++)
            if(i+i>j&&i+j>i)fr<<i<<" "<<i<<" "<<j<<endl;

    fd.close();
    fr.close();
    return 0;
}
