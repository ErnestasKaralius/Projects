#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int sk; // Batų porų skaičius
    char P[99]; // Vyriška ar moteriška pora
    double K[99]; // Kainos
    double vsum=0,msum=0; // Vyriškų ir moteriškų batų sumos
    int vsk=0,msk=0; // Vyriškų ir moteriškų batų skaičius
    int i;
    ifstream fd ("avalyne_data.txt");
    ofstream fr ("avalyne_rez.txt");
    fd>>sk;
    // Nuskaitymas
    for(i=0;i<sk;i++) fd>>P[i]>>K[i];
    // Moteriškų ir vyriškų batų kainų suma
    for(i=0;i<sk;i++)
    {
        if(P[i]=='v') {vsum=vsum+K[i];vsk++;}
            else {msum=msum+K[i];msk++;}
    }
    fr<<fixed<<setprecision(2)<<"Moteriška avalynė:\n";
    if(msk==0) fr<<"Prekiauta nebuvo\n";
        else
        {
            fr<<"Iš viso: "<<msum<<endl;
            fr<<"Vidutiniškai kainavo: "<<msum/msk;
        }

    fr<<"\nVyriška avalynė:\n";
    if(vsk==0) fr<<"Prekiauta nebuvo\n";
        else
        {
            fr<<"Iš viso: "<<vsum<<endl;
            fr<<"Vidutiniškai kainavo: "<<vsum/vsk<<endl;
        }
    fr<<"Iš viso parduota: "<<vsum+msum;

    fd.close();
    fr.close();
    return 0;
}
