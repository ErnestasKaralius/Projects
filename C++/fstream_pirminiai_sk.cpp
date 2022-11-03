#include <fstream>
using namespace std;

int main()
{
    int a,sk,n,i,suma,k=1;
    ifstream fd("pirminiai_data.txt");
    ofstream fr("pirminiai_rez.txt");
    fd>>a>>n;
    for(sk=a+1;k<=n;sk++)
    {
        suma=0;
        for(i=2;i<sk;i++) if(sk%i==0)suma++;
        if(suma==0){k++;fr<<sk<<endl;}
    }

    fd.close();
    fr.close();
    return 0;
}
