#include <fstream>
#include <cmath>
using namespace std;
int neismoko_zodziu(int zsk,int z);

int main()
{
    int d; // Dienų skaièius
    int z; // Kiek turi išmokti žodžių per dieną
    int dt=0; // Kiek dienų neišmoko pakankamai žodžių
    int zsk; // Žodžių skaičius
    int neismoko=0; // Kiek iš viso žodžių neišmoko
    ifstream fd("planas_data.txt");
    ofstream fr("planas_rez.txt");
    fd>>d>>z;
    for(int i=0;i<d;i++)
    {
        fd>>zsk;
        if(zsk<z) dt++;
        neismoko=neismoko+neismoko_zodziu(zsk,z);

    }
    fr<<dt<<endl;
    fr<<neismoko<<endl;
    fr<<ceil((double)neismoko/z);


    fd.close();
    fr.close();
    return 0;
}

int neismoko_zodziu(int zsk,int z)
{
    int liko_ismokti=z-zsk;

    return liko_ismokti;
}
