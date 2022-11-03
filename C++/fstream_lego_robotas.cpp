#include <fstream>
using namespace std;

int main()
{
    int n,i,j;
    double a,m,suma=0;
    ifstream fd("lego_data.txt");
    ofstream fr("lego_rez.txt");
    for(i=1;i<=6;i++)
    {
        fd>>n;
        for(j=1;j<=n;j++)
        {
            fd>>m;
            suma=suma+m;
        }
    }
    fr<<suma<<endl;
    fd>>a;
    if(suma<a)fr<<"NE";
        else fr<<"TAIP";

    fd.close();
    fr.close();
    return 0;
}
