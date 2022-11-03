#include <fstream>
using namespace std;

int main()
{
    int d,i,suma=0,M[92],nelijo=0;
    double vid;
    ifstream fd("krituliai_data.txt");
    ofstream fr("krituliai_rez.txt");
    fd>>d;
    for(i=0;i<d;i++) fd>>M[i];
    //Suma
    for(i=0;i<d;i++) suma=suma+M[i];
    // Kiek dienų nelijo
    for(i=0;i<d;i++) if(M[i]==0)nelijo++;
    // Vidurkis
    vid=(double)suma/(d-nelijo);

    fr<<suma<<endl;
    fr<<nelijo<<endl;
    fr<<vid;

    fd.close();
    fr.close();
    return 0;
}
