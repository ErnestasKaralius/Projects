#include <fstream>
#include <cmath>
using namespace std;
int reikes_plyteliu(int x,int y,int sx,int sy);

int main()
{
    ifstream fd("plyteliu_klojimas_data.txt");
    ofstream fr("plyteliu_klojimas_rez.txt");
    int x,y; // Plytelės ilgis ir plotis centimetrais
    int sx,sy; // Grindų ilgis ir plotis metrais
    fd>>x>>y>>sx>>sy;
    // Kambario matmenų keitimas į centimetrus
    sx=sx*100;sy=sy*100;

    fr<<reikes_plyteliu(x,y,sx,sy);

    fd.close();
    fr.close();
    return 0;
}

int reikes_plyteliu(int x,int y,int sx,int sy)
{
    int plyteles;
    plyteles=ceil((double)sx/x)*ceil((double)sy/y);

    return plyteles;
}
