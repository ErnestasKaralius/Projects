#include <fstream>
using namespace std;

int main()
{
    int n,i,gn,gs,j,sk,suma1=0,suma2=0,suma3=0,suma4=0;
    ifstream fd("gamykla_data.txt");
    ofstream fr("gamykla_rez.txt");
    fd>>n;
    for(i=1;i<=n;i++)
    {
        fd>>gn>>gs;
        for(j=1;j<=gs;j++)
        {
            fd>>sk;
            if(gn==1)suma1=suma1+sk;
                else if(gn==2)suma2=suma2+sk;
                    else if(gn==3)suma3=suma3+sk;
                        else suma4=suma4+sk;
        }
    }
    fr<<"Pjaustyklė: "<<suma1<<endl;
    fr<<"Virdulys: "<<suma2<<endl;
    fr<<"Mikseris: "<<suma3<<endl;
    fr<<"Plaktuvė: "<<suma4<<endl;

    if(suma1>suma2&&suma1>suma3&&suma1>suma4)fr<<"Daugiausia: pjaustuvė";
        else if(suma2>suma1&&suma2>suma3&&suma2>suma4)fr<<"Daugiausia: virdulys";
            else if(suma3>suma1&&suma3>suma2&&suma3>suma4)fr<<"Daugiausia: mikseris";
                else fr<<"Daugiausia: plaktuvė";

    fd.close();
    fr.close();
    return 0;
}
