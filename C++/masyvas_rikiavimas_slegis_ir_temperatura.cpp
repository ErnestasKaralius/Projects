#include <fstream>
using namespace std;

int main()
{
    int T[365],P[365]; // Paros temperatūros ir slėgio vidurkiai
    int p; // Parų skaičius
    int kiek=0; // Paros iš eilės
    int did=1; // Daugiausia parų iš eilės
    int i;
    ifstream fd("slegis_ir_temperatura_data.txt");
    ofstream fr("slegis_ir_temperatura_rez.txt");
    fd>>p;
    for(i=0;i<p;i++) fd>>T[i]>>P[i];

    for(i=0;i<p;i++)
    {
        if(T[i]>0&&P[i]>P[0]) {kiek++; if(kiek>did) did=kiek;}
            else kiek=0;
    }
    fr<<did;

    fd.close();
    fr.close();
    return 0;
}
