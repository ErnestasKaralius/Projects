#include <fstream>
using namespace std;

int main()
{
    int n,i,j,sk,suma,bsk,gsk,ivert,galut,eile;
    ifstream fd("pietus_data.txt");
    ofstream fr("pietus_rez.txt");
    fd>>n;
    for(i=1;i<=n;i++)
    {
        ivert=0;
        suma=0;
        for(j=1;j<n;j++)
        {
            fd>>sk;
            if(j==1){bsk=sk;gsk=sk;}
            if(sk>gsk)gsk=sk;
            if(sk<bsk)bsk=sk;
            suma=suma+sk;
        }
        ivert=suma-gsk-bsk;
        if(i==1){eile=i;galut=ivert;}
        if(ivert>galut){eile=i;galut=ivert;}
    }
    fr<<eile<<" "<<galut;

    fd.close();
    fr.close();
    return 0;
}
