#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int k; // Dienų kiekis
    double a,b,c; // Turima pinigų suma
    double A[99],B[99],C[99];
    double asuma=0,bsuma=0,csuma=0;
    int sk=0;
    int i;
    ifstream fd("taupymas_data.txt");
    ofstream fr("taupymas_rez.txt");
    fd>>k>>a>>b>>c;
    //Nuskaitymas
    for(i=0;i<k;i++) fd>>A[i]>>B[i]>>C[i];
    // Kiek kiekvienas vaikinas išleido
    for(i=0;i<k;i++)
    {
        asuma=asuma+A[i];
        bsuma=bsuma+B[i];
        csuma=csuma+C[i];
    }
    fr<<fixed<<setprecision(2)<<"Vaikinai išleido: "<<asuma<<" "<<bsuma<<" "<<csuma<<endl;
    fr<<"Dienos išlaidų vidurkis: "<<asuma/k<<" "<<bsuma/k<<" "<<csuma/k<<endl;
    fr<<"Vaikinams liko pinigų: "<<a-asuma<<" "<<b-bsuma<<" "<<c-csuma<<endl;
    // Kiek dienų vaikinai išleido daugiau už savo vidurkį
    for(i=0;i<k;i++)
    {
        if(A[i]>asuma/k) sk++;
        if(B[i]>bsuma/k) sk++;
        if(C[i]>csuma/k) sk++;
    }
    fr<<"Dienos, kai išleido daugiau už vidurkį: "<<sk;

    fd.close();
    fr.close();
    return 0;
}
