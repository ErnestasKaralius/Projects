#include <fstream>
using namespace std;

int main()
{
    int a,b,x,k1,k2;
    ifstream fd ("staciakampis_data.txt");
    ofstream fr ("staciakampis_rez.txt");
    fd>>a>>b>>x;
    for (k1=a; k1<=b; k1++)
    {
        k2=k1+x;
        if (k2<=b) fr<<k1<<" "<<k2<<endl;
    }

    fd.close();
    fr.close();
    return 0;
}
