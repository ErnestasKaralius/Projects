#include <fstream>
using namespace std;
int vidurkis();
int aukstesnis(int vid);

int main()
{
    ofstream fr("funkcijos_ugiai_rez.txt");
    int vid=vidurkis();
    fr<<vid<<" "<<aukstesnis(vid);
    fr.close();
    return 0;
}

int vidurkis()
{
    int x,suma=0,ugis,vid;
    ifstream fd("funkcijos_ugiai_data.txt");
    fd>>x;
    for(int i=0;i<x;i++) {fd>>ugis;suma=suma+ugis;}
    vid=suma/x;

    fd.close();
    return vid;
}

int aukstesnis(int vid)
{
    int x,ugis,kiekis=0;
    ifstream fd("funkcijos_ugiai_data.txt");
    fd>>x;
    for(int i=0;i<x;i++)
    {
        fd>>ugis;
        if(ugis>vid) kiekis++;
    }
    fd.close();
    return kiekis;
}
