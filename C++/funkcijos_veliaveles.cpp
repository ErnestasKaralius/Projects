#include <fstream>
using namespace std;

int suklijuota(int geltona, int zalia, int raudona);

int main()
{
    int n;
    char spalva;
    int geltona=0,zalia=0,raudona=0;
    int sk;

    ifstream fd("veliaveles_data.txt");
    fd>>n;
    for(int i=0; i<n; i++)
    {
        fd>>spalva>>sk;
        if(spalva == 'G') geltona+=sk;
            else if(spalva == 'Z') zalia+=sk;
                else raudona+=sk;
    }
    fd.close();

    sk=suklijuota(geltona,zalia,raudona);

    ofstream fr("veliaveles_rez.txt");
    fr<<sk;
    fr<<"\nG = "<<geltona-sk*2;
    fr<<"\nZ = "<<zalia-sk*2;
    fr<<"\nR = "<<raudona-sk*2;

    fr.close();

    return 0;
}

int suklijuota(int geltona, int zalia, int raudona)
{
    int kiekis=geltona/2;

    if(zalia < geltona && zalia < raudona) kiekis=zalia/2;
        else if(raudona < geltona && raudona < zalia) kiekis=raudona/2;

    return kiekis;
}
